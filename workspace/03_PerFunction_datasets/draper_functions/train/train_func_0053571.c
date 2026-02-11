csRemove(giopConnection* conn)
{
  ASSERT_OMNI_TRACEDMUTEX_HELD(pd_lock,1);

  connectionState* cs = 0;

  connectionState** head = &(pd_connectionState[((omni::ptr_arith_t)conn)%
						connectionState::hashsize]);
  while (*head) {
    if ((*head)->connection == conn) {
      cs = *head;
      *head = cs->next;
      pd_nconnections--;
      if (orbParameters::threadPerConnectionPolicy) {


	if (!pd_thread_per_connection &&
	    pd_nconnections <= orbParameters::threadPerConnectionLowerLimit) {
	  pd_thread_per_connection = 1;
	}
      }
      break;
    }
    else {
      head = &((*head)->next);
    }
  }
  return cs;
}
