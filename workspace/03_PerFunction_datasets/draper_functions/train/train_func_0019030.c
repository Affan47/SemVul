incrementaldelaunay(struct mesh *m, struct behavior *b)
#else
long incrementaldelaunay(m, b)
struct mesh *m;
struct behavior *b;
#endif

{
  struct otri starttri;
  vertex vertexloop;


  boundingbox(m, b);
  if (b->verbose) {
    printf("  Incrementally inserting vertices.\n");
  }
  traversalinit(&m->vertices);
  vertexloop = vertextraverse(m);
  while (vertexloop != (vertex) NULL) {
    starttri.tri = m->dummytri;
    if (insertvertex(m, b, vertexloop, &starttri, (struct osub *) NULL, 0, 0)
        == DUPLICATEVERTEX) {
      if (!b->quiet) {
        printf(
"Warning:  A duplicate vertex at (%.12g, %.12g) appeared and was ignored.\n",
               vertexloop[0], vertexloop[1]);
      }
      setvertextype(vertexloop, UNDEADVERTEX);
      m->undeads++;
    }
    vertexloop = vertextraverse(m);
  }

  return removebox(m, b);
}
