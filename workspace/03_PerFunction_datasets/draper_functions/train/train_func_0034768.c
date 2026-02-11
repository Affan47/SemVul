_glh_add_history(GlHistory *glh, const char *line, int force)
{
  int slen;
  int empty;
  const char *nlptr;
  GlhHashNode *hnode;
  GlhLineNode *lnode;
  int i;


  if(!glh || !line) {
    errno = EINVAL;
    return 1;
  };


  if(!glh->enable || !glh->buffer || glh->max_lines == 0)
    return 0;


  if(_glh_cancel_search(glh))
    return 1;


  nlptr = strchr(line, '\n');
  if(nlptr)
    slen = (nlptr - line);
  else
    slen = strlen(line);


  empty = 1;
  for(i=0; i<slen && empty; i++)
    empty = isspace((int)(unsigned char) line[i]);


  if(empty && !force)
    return 0;


  if(glh->max_lines >= 0) {


    while(glh->nline > 0 && glh->nline >= glh->max_lines)
      _glh_discard_line(glh, glh->list.head);


    if(glh->max_lines == 0)
      return 0;
  };


  hnode = _glh_acquire_copy(glh, line, slen);
  if(!hnode) {
    _err_record_msg(glh->err, "No room to store history line", END_ERR_MSG);
    errno = ENOMEM;
    return 1;
  };


  lnode = (GlhLineNode *) _new_FreeListNode(glh->list.node_mem);


  if(!lnode) {
    hnode = _glh_discard_copy(glh, hnode);
    _err_record_msg(glh->err, "No room to store history line", END_ERR_MSG);
    errno = ENOMEM;
    return 1;
  };


  lnode->id = glh->seq++;
  lnode->timestamp = time(NULL);
  lnode->group = glh->group;
  lnode->line = hnode;


  if(glh->list.head)
    glh->list.tail->next = lnode;
  else
    glh->list.head = lnode;
  lnode->next = NULL;
  lnode->prev = glh->list.tail;
  glh->list.tail = lnode;


  glh->nline++;
  return 0;
}
