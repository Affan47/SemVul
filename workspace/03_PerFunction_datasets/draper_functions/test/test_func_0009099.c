ftp_state_stor_resp(struct connectdata *conn,
                                    int ftpcode)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct FTP *ftp = data->reqdata.proto.ftp;

  if(ftpcode>=400) {
    failf(data, "Failed FTP upload: %0d", ftpcode);

    return CURLE_FTP_COULDNT_STOR_FILE;
  }

  if(data->set.ftp_use_port) {


    result = AllowServerConnect(conn);
    if( result )
      return result;
  }

  if(conn->ssl[SECONDARYSOCKET].use) {


    infof(data, "Doing the SSL/TLS handshake on the data stream\n");

    result = Curl_ssl_connect(conn, SECONDARYSOCKET);
    if(result)
      return result;
  }

  *(ftp->bytecountp)=0;


  Curl_pgrsSetUploadSize(data, data->set.infilesize);

  result = Curl_setup_transfer(conn, -1, -1, FALSE, NULL,
                               SECONDARYSOCKET, ftp->bytecountp);
  state(conn, FTP_STOP);

  return result;
}
