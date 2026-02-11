connection_vote(struct connection *pconn,
                     struct vote *pvote,
                     enum vote_type type)
{
  struct vote_cast *pvc;

  if (!conn_can_vote(pconn, pvote)) {
    return;
  }


  if ((pvc = vote_cast_find(pvote, pconn->id))) {
    pvc->vote_cast = type;
  } else if ((pvc = vote_cast_new(pvote))) {
    pvc->vote_cast = type;
    pvc->conn_id = pconn->id;
  } else {

    log_error("Failed to create a vote cast for connection %s.",
              pconn->username);
    return;
  }
  check_vote(pvote);
}
