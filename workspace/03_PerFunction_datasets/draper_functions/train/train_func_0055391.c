Curl_fillreadbuffer(struct connectdata *conn, int bytes, int *nreadp)
{
  struct SessionHandle *data = conn->data;
  size_t buffersize = (size_t)bytes;
  int nread;

  if(conn->bits.upload_chunky) {

    buffersize -= (8 + 2 + 2);
    data->reqdata.upload_fromhere += 10;
  }


  nread = (int)conn->fread(data->reqdata.upload_fromhere, 1,
                           buffersize, conn->fread_in);

  if(nread == CURL_READFUNC_ABORT) {
    failf(data, "operation aborted by callback\n");
    return CURLE_ABORTED_BY_CALLBACK;
  }

  if(!conn->bits.forbidchunk && conn->bits.upload_chunky) {

    char hexbuffer[11];
    int hexlen = snprintf(hexbuffer, sizeof(hexbuffer),
                          "%x\r\n", nread);

    data->reqdata.upload_fromhere -= hexlen;
    nread += hexlen;


    memcpy(data->reqdata.upload_fromhere, hexbuffer, hexlen);


    memcpy(data->reqdata.upload_fromhere + nread, "\r\n", 2);

    if((nread - hexlen) == 0) {

      data->reqdata.keep.upload_done = TRUE;
    }

    nread+=2;
  }

  *nreadp = nread;

#ifdef CURL_DOES_CONVERSIONS
  if(data->set.prefer_ascii) {
    CURLcode res;
    res = Curl_convert_to_network(data, data->reqdata.upload_fromhere, nread);

    if(res != CURLE_OK) {
      return(res);
    }
  }
#endif

  return CURLE_OK;
}
