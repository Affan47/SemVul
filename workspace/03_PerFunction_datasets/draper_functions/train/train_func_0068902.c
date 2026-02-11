ftp_state_timeout(struct connectdata *conn)
{
  struct SessionHandle *data=conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  long timeout_ms=360000;

  if(data->set.ftp_response_timeout )


    timeout_ms = data->set.ftp_response_timeout*1000 -
      Curl_tvdiff(Curl_tvnow(), ftpc->response);
  else if(data->set.timeout)

    timeout_ms = data->set.timeout*1000 -
      Curl_tvdiff(Curl_tvnow(), conn->now);
  else


    timeout_ms = ftpc->response_time*1000 -
      Curl_tvdiff(Curl_tvnow(), ftpc->response);

  return timeout_ms;
}
