SetFlag(unsigned long id, int t)
{
  struct icon_info *tmp;
  tmp = Head;

  while(tmp != NULL){
    if (tmp->id == id){
      if (t == M_ICONIFY)
	tmp->flags |= ICONIFIED;
       else
	tmp->flags ^= ICONIFIED;
      return tmp;
    }
    tmp = tmp->next;
  }
  return NULL;
}
