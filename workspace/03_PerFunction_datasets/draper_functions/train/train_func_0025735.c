Curl_pp_state_timeout(struct pingpong *pp)
{
  struct connectdata *conn = pp->conn;
  struct SessionHandle *data=conn->data;
  long timeout_ms;
  long timeout2_ms;
  long response_time= (data->set.server_response_timeout)?
    data->set.server_response_timeout: pp->response_time;


  timeout_ms = response_time -
    Curl_tvdiff(Curl_tvnow(), pp->response);

  if(data->set.timeout) {

    timeout2_ms = data->set.timeout -
      Curl_tvdiff(Curl_tvnow(), conn->now);


    timeout_ms = CURLMIN(timeout_ms, timeout2_ms);
  }

  return timeout_ms;
}
