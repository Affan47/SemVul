mime_client_write_open(struct soap *soap, void *unused_handle, const char *id, const char *type, const char *description, enum soap_mime_encoding encoding)
{
  FILE *fd;
  const char *file;
  fprintf(stderr, "Opening streaming inbound MIME channel for id=%s type=%s\n", id, type);

  file = *(char**)soap->user;
  soap->user = (void*)(((char**)soap->user)+1);
  fd = fopen(file, "wb");
  if (!fd)
    soap->error = soap_receiver_fault(soap, "Cannot save data to file", file);
  return (void*)fd;
}
