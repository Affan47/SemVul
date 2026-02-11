queue_close(QUEUE *queue){
  int err;
  assert(queue);
  err = FALSE;
  if(!vlclose(queue->db)) err = TRUE;
  free(queue);
  return err ? FALSE : TRUE;
}
