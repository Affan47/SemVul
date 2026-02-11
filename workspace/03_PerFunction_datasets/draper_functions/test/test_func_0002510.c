handle_vote_submit(struct connection *pconn, int vote_no, int value)
{
  struct vote *pvote;
  enum vote_type type;

  log_debug("Got vote submit (%d %d) from %s.",
            vote_no, value, conn_description(pconn));

  pvote = get_vote_by_no(vote_no);
  if (pvote == NULL) {


    log_verbose("Submit request for unknown vote_no %d from %s ignored.",
                vote_no, conn_description(pconn));
    return;
  }

  if (value == 1) {
    type = VOTE_YES;
  } else if (value == -1) {
    type = VOTE_NO;
  } else if (value == 0) {
    type = VOTE_ABSTAIN;
  } else {
    log_error("Invalid packet data for submit of vote %d "
              "from %s ignored.", vote_no, conn_description(pconn));
    return;
  }

  connection_vote(pconn, pvote, type);
}
