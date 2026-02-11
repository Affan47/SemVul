main()
{ SOAP_SOCKET m;
#if defined(_POSIX_THREADS) || defined(_SC_THREADS)
  pthread_t tid;
#endif
  struct soap soap, *tsoap;

  signal(SIGPIPE, sigpipe_handle);
  if (CRYPTO_thread_setup())
  { fprintf(stderr, "Cannot setup thread mutex for OpenSSL\n");
    exit(1);
  }

  soap_init(&soap);


  if (soap_ssl_server_context(&soap,
    SOAP_SSL_DEFAULT,
    "server.pem",
    "password",
    "cacert.pem",
    NULL,
    "dh512.pem",
    NULL,
    "sslserver"
  ))
  { soap_print_fault(&soap, stderr);
    exit(1);
  }
  soap.accept_timeout = 60;
  soap.send_timeout = soap.recv_timeout = 30;
  m = soap_bind(&soap, NULL, 18081, 100);
  if (!soap_valid_socket(m))
  { soap_print_fault(&soap, stderr);
    exit(1);
  }
  fprintf(stderr, "Bind successful: socket = %d\n", m);
  for (;;)
  { SOAP_SOCKET s = soap_accept(&soap);
    if (!soap_valid_socket(s))
    { if (soap.errnum)
        soap_print_fault(&soap, stderr);
      else
        fprintf(stderr, "Server timed out (timeout set to %d seconds)\n", soap.accept_timeout);
      break;
    }
    fprintf(stderr, "Socket %d connection from IP %d.%d.%d.%d\n", s, (int)(soap.ip>>24)&0xFF, (int)(soap.ip>>16)&0xFF, (int)(soap.ip>>8)&0xFF, (int)soap.ip&0xFF);
    tsoap = soap_copy(&soap);
    if (!tsoap)
    { soap_closesock(&soap);
      continue;
    }
#if defined(_POSIX_THREADS) || defined(_SC_THREADS)
    pthread_create(&tid, NULL, (void*(*)(void*))&process_request, tsoap);
#else
    process_request(tsoap);
#endif
  }
  soap_destroy(&soap);
  soap_end(&soap);
  soap_done(&soap);
  CRYPTO_thread_cleanup();
  return 0;
}
