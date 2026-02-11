list_cat(node l1,node l2){
  node ptr=l1;
  if (ptr==0) return l2;
  while(Cdr(ptr)!=0) ptr=Cdr(ptr);
  node_set_ptr(ptr,(void *)l2,NODE,RIGHT);
  return l1;
}
