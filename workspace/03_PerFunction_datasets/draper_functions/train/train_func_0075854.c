qs_GCEvent(qs_event_t **l_qs_event) {
  qs_event_t *lp = *l_qs_event;
  qs_event_t *lpl = lp;
  time_t gmt_time;
  qs_time(&gmt_time);
  if(*l_qs_event == NULL) {
    return;
  }
  while(lp) {

    if(lp->time < (gmt_time - m_qs_expiration)) {
      qs_event_t *tmp = lp;
      if(lpl == lp) {

	lpl = lp->next;
	lp = lp->next;
	*l_qs_event = lpl;
      } else {
	lpl->next = lp->next;
	lp = lp->next;
      }
      qs_freeEvent(tmp);
    }
    if(lp != NULL) {
      lpl = lp;
      lp = lp->next;
    }
  }
}
