save(const char *file)
{ struct soap soap;
  soap_init(&soap);
  soap_begin(&soap);
  if (file)
    soap.sendfd = open(file, O_CREAT|O_TRUNC|O_WRONLY, S_IREAD|S_IWRITE);
  if (soap.sendfd < 0)
    return -1;
  soap_begin_send(&soap);
  for (int i = 0; i < POOLSIZE; i++)
    if (ref[i])
    { ref[i]->soap_serialize(&soap);
      soap_begin_send(&soap);
      ref[i]->soap_put(&soap, "item", NULL);
      soap_end_send(&soap);
    }
  if (file)
    close(soap.sendfd);
  soap_end(&soap);
  soap_done(&soap);
  return 0;
}
