K_request_process_status(MessageEnvelope* msg) {
  PCB* next = pq_peek(_process_list);
  char tmp_buf[20];
  strcpy(msg->data, "");
  while (next != NULL) {
    sprintf(tmp_buf, "%d,%d,%d\n", next->pid,
    				   next->state,
				   next->priority);
    strcat(msg->data, tmp_buf);
    next = next->p_next;
  }

  return 0;
}
