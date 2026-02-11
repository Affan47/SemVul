listsetalloc(List* sq, unsigned int sz)
{
  elem_t* newcontent;
  if(sq == NULL) return FALSE;
  if(sz <= 0) {sz = (sq->length?2*sq->length:DEFAULTALLOC);}
  else if(sq->alloc >= sz) {return TRUE;}
  newcontent=(elem_t*)ecalloc(sz,sizeof(elem_t));
  if(sq->alloc > 0 && sq->length > 0 && sq->content != NULL) {
    memcpy((void*)newcontent,(void*)sq->content,sizeof(elem_t)*sq->length);
    efree(sq->content);
  }
  sq->content=newcontent;
  sq->alloc=sz;
  return TRUE;
}
