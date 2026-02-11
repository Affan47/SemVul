stable_point()
{

  return fd.get() >= 0 && num_req_bufd == 0 && num_req_sent == 0 &&
    num_req_rcvd == 0 && response_end_offset == 0;
}
