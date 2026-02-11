nss_load_crl(const char* crlfilename)
{
  PRFileDesc *infile;
  PRFileInfo  info;
  SECItem filedata = { 0, NULL, 0 };
  SECItem crlDER = { 0, NULL, 0 };
  char *body;

  infile = PR_Open(crlfilename, PR_RDONLY, 0);
  if(!infile)
    return SECFailure;

  if(PR_SUCCESS != PR_GetOpenFileInfo(infile, &info))
    goto fail;

  if(!SECITEM_AllocItem(NULL, &filedata, info.size +  1))
    goto fail;

  if(info.size != PR_Read(infile, filedata.data, info.size))
    goto fail;


  body = (char*)filedata.data;
  body[--filedata.len] = '\0';

  body = strstr(body, "-----BEGIN");
  if(body) {

    char *trailer;
    char *begin = PORT_Strchr(body, '\n');
    if(!begin)
      begin = PORT_Strchr(body, '\r');
    if(!begin)
      goto fail;

    trailer = strstr(++begin, "-----END");
    if(!trailer)
      goto fail;


    *trailer = '\0';
    if(ATOB_ConvertAsciiToItem(&crlDER, begin))
      goto fail;

    SECITEM_FreeItem(&filedata, PR_FALSE);
  }
  else

    crlDER = filedata;

  PR_Close(infile);
  return nss_cache_crl(&crlDER);

fail:
  PR_Close(infile);
  SECITEM_FreeItem(&filedata, PR_FALSE);
  return SECFailure;
}
