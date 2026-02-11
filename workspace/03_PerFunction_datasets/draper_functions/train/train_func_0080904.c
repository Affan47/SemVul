GListPop(gl)
GList gl;
{
  void *thing;
  struct GNodeP *f;

  if (gl->head != NULL)
  {
    thing = gl->head->thing;
    f = gl->head;
    if (gl->head != NULL) gl->head = gl->head->next;
    if (gl->head != NULL) gl->head->prev = NULL;
    gl->c = gl->head;
    FreeListNode(gl, f);

    return(thing);
  }
  return(NULL);
}
