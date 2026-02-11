dequeue_query(struct query_node *qun) {
  LIST_UNLINK(outstanding,qun);
  free(qun->id);
  free(qun->owner);
  free(qun);
}
