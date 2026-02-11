Curl_Transfer(struct connectdata *c_conn,
              int sockindex,
              curl_off_t size,
              bool getheader,
              curl_off_t *bytecountp,
              int writesockindex,


              curl_off_t *writecountp

              )
{
  struct connectdata *conn = (struct connectdata *)c_conn;
  if(!conn)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  curlassert((sockindex <= 1) && (sockindex >= -1));


  conn->sockfd = sockindex==-1?
    CURL_SOCKET_BAD:conn->sock[sockindex];
  conn->size = size;
  conn->bits.getheader = getheader;
  conn->bytecountp = bytecountp;
  conn->writesockfd = writesockindex==-1?
    CURL_SOCKET_BAD:conn->sock[writesockindex];
  conn->writebytecountp = writecountp;

  return CURLE_OK;

}
