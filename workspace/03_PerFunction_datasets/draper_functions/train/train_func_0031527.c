InitiateTransfer(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  struct FTP *ftp = data->req.protop;
  CURLcode result = CURLE_OK;

  if(conn->ssl[SECONDARYSOCKET].use) {


    infof(data, "Doing the SSL/TLS handshake on the data stream\n");
    result = Curl_ssl_connect(conn, SECONDARYSOCKET);
    if(result)
      return result;
  }

  if(conn->proto.ftpc.state_saved == FTP_STOR) {
    *(ftp->bytecountp)=0;


    Curl_pgrsSetUploadSize(data, data->set.infilesize);


    Curl_sndbufset(conn->sock[SECONDARYSOCKET]);

    Curl_setup_transfer(conn, -1, -1, FALSE, NULL,
                        SECONDARYSOCKET, ftp->bytecountp);
  }
  else {

    Curl_setup_transfer(conn, SECONDARYSOCKET,
                        conn->proto.ftpc.retr_size_saved, FALSE,
                        ftp->bytecountp, -1, NULL);
  }

  conn->proto.ftpc.pp.pending_resp = TRUE;
  state(conn, FTP_STOP);

  return CURLE_OK;
}
