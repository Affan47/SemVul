cell_new(int n,int r){
  cell c;
  int i;
  if ((c=(cell)mem_malloc(sizeof(struct cell_t)))==0)
                bad_error("malloc failed in cell_new()");
  if ((c->points=(Ipnt *)mem_malloc((n+1)*sizeof(Ipnt)))==0)
                bad_error("malloc failed in cell_new()");
  if ((c->ptrs=(cell *)mem_malloc((n+1)*sizeof(cell)))==0)
                bad_error("malloc failed in cell_new()");
  c->H=HMnew(n,n+1);
  c->U=HMnew(n,n);
  c->T=Ivector_new(r);
  c->norm=HVnew(n+1);
  c->n=n;
  c->r=r;
  c->id=next_id++;
  c->freeptrs=n+1;
  c->volume=0;
  c->Tindx=0;
  c->next=0;
  for(i=0;i<=n;i++) {c->ptrs[i]=0; c->points[i]=0;}
  return c;
}
