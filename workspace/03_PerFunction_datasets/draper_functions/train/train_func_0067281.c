Next() {
  if(IsEmpty()) return NULL;
  if(!cur->next) return NULL;
  cur=cur->next;
  return(cur->o);
}
