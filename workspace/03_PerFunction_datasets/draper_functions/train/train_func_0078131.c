kfree(char *v, int len)
{
  struct run *r, *rend, **rp, *p, *pend;

  if(len <= 0 || len % PAGE)
    panic("kfree");


  memset(v, 1, len);

  acquire(&kalloc_lock);
  p = (struct run*)v;
  pend = (struct run*)(v + len);
  for(rp=&freelist; (r=*rp) != 0 && r <= pend; rp=&r->next){
    rend = (struct run*)((char*)r + r->len);
    if(r <= p && p < rend)
      panic("freeing free page");
    if(pend == r){
      p->len = len + r->len;
      p->next = r->next;
      *rp = p;
      goto out;
    }
    if(rend == p){
      r->len += len;
      if(r->next && r->next == pend){
        r->len += r->next->len;
        r->next = r->next->next;
      }
      goto out;
    }
  }

  p->len = len;
  p->next = r;
  *rp = p;

 out:
  release(&kalloc_lock);
}
