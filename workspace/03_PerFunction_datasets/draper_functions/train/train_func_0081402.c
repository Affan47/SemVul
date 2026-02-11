open_data(struct soap *soap, const char *file, struct x__Data *data)
{ struct stat sb;
  FILE *fd = NULL;
  int size;
  soap_default_x__Data(soap, data);
  fd = fopen(file, "rb");
  if (!fd)
  { fprintf(stderr, "Cannot open file %s\n", file);
    return soap->error = SOAP_EOF;
  }

  data->xop__Include.__ptr = (unsigned char*)fd;
  if (!fstat(fileno(fd), &sb) && sb.st_size > 0)
    size = sb.st_size;
  else
  {
    soap_set_omode(soap, SOAP_IO_CHUNK);
    size = 0;
  }
  data->xop__Include.__size = size;
  data->xmime5__contentType = file_type(file);
  data->xop__Include.id = NULL;
  data->xop__Include.type = data->xmime5__contentType;
  data->xop__Include.options = NULL;
  return SOAP_OK;
}
