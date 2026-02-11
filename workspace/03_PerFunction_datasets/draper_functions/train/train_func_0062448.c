strcpy_from_child(struct tcb* tcp, long addr) {
  char* ret = strcpy_from_child_or_null(tcp, addr);
  EXITIF(ret == NULL);
  return ret;
}
