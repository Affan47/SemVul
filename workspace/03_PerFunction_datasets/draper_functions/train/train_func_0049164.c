find_session_by_id (GstRTPDec * rtpdec, gint id)
{
  GSList *walk;

  for (walk = rtpdec->sessions; walk; walk = g_slist_next (walk)) {
    GstRTPDecSession *sess = (GstRTPDecSession *) walk->data;

    if (sess->id == id)
      return sess;
  }
  return NULL;
}
