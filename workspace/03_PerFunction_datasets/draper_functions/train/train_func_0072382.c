est_node_iter_next(ESTNODE *node){
  ESTDOC *doc;
  char *vbuf;
  if(!node->ilist) return NULL;
  if(cblistnum(node->ilist) < 1){
    cblistclose(node->ilist);
    node->ilist = cblistopen();
    if((est_node_read_list(node) == -1 || cblistnum(node->ilist) < 1)) return NULL;
  }
  vbuf = cblistshift(node->ilist, NULL);
  doc = *(ESTDOC **)vbuf;
  free(vbuf);
  return doc;
}
