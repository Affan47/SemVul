inject_split_check(struct http_request* req,
                             struct http_response* res) {

  DEBUG_MISC_CALLBACK(req, res);


  if (res->state != STATE_OK) {
    handle_error(req, res, (u8*)"during header injection attacks", 0);
    return 0;
  }


  if (GET_HDR((u8*)"Skipfish-Inject", &MRES(0)->hdr))
    problem(PROB_HTTP_INJECT, MREQ(0), MRES(0),
      (u8*)"successfully injected 'Skipfish-Inject' header into response",
      req->pivot, 0);

  if (GET_HDR((u8*)"Skipfish-Inject", &MRES(1)->hdr))
    problem(PROB_HTTP_INJECT, MREQ(1), MRES(1),
      (u8*)"successfully injected 'Skipfish-Inject' header into response",
      req->pivot, 0);

  return 0;
}
