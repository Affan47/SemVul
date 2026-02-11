nasty_vertical(graph *g, mesh *m, int A, int B, int limit){
  if(limit == 0) return;
  if(A+(m->width*2) > B)return;

  add_edge(g,m->v[A],m->v[B]);

  A+=m->width;
  B-=m->width;
  nasty_vertical(g,m,A,B,limit-1);
}
