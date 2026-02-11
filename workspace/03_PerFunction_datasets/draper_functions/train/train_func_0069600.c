main(int argc, char **argv)
{ int m, s;
  struct soap soap;
  Factory factory;
  soap_init(&soap);
  soap.user = (void*)&factory;
  soap.accept_timeout = 1;
  if (argc < 2)
  { factory.load("factory.dat");
    factory.purge(&soap);
    soap_serve(&soap);
    factory.save("factory.dat");
  }
  else
  { m = soap_bind(&soap, NULL, atoi(argv[1]), 100);
    if (m < 0)
    { soap_print_fault(&soap, stderr);
      exit(1);
    }
    fprintf(stderr, "Socket connection successful %d\n", m);
    for (int i = 1; ; i++)
    { s = soap_accept(&soap);
      if (s < 0)
      { if (soap.errnum)
          soap_print_fault(&soap, stderr);
	else
	{ factory.purge(&soap);
	  continue;
	}
	exit(1);
      }
      fprintf(stderr, "%d: accepted %d IP=%d.%d.%d.%d ... ", i, s, (int)(soap.ip>>24)&0xFF, (int)(soap.ip>>16)&0xFF, (int)(soap.ip>>8)&0xFF, (int)soap.ip&0xFF);
      soap_serve(&soap);
      fprintf(stderr, "served\n");
      soap_end(&soap);
    }
  }
  return 0;
}
