process_request(struct soap *soap)
{
#if defined(_POSIX_THREADS) || defined(_SC_THREADS)
  pthread_detach(pthread_self());
#endif
  if (soap_ssl_accept(soap) != SOAP_OK)
  {
    soap_print_fault(soap, stderr);
    fprintf(stderr, "SSL request failed, continue with next call...\n");
  }
  else
    soap_serve(soap);
  soap_destroy(soap);
  soap_end(soap);
  soap_free(soap);
  return NULL;
}
