frontlocate(struct mesh *m, struct splaynode *splayroot,
                              struct otri *bottommost, vertex searchvertex,
                              struct otri *searchtri, int *farright)
#else
struct splaynode *frontlocate(m, splayroot, bottommost, searchvertex,
                              searchtri, farright)
struct mesh *m;
struct splaynode *splayroot;
struct otri *bottommost;
vertex searchvertex;
struct otri *searchtri;
int *farright;
#endif

{
  int farrightflag;
  triangle ptr;

  otricopy(*bottommost, *searchtri);
  splayroot = splay(m, splayroot, searchvertex, searchtri);

  farrightflag = 0;
  while (!farrightflag && rightofhyperbola(m, searchtri, searchvertex)) {
    onextself(*searchtri);
    farrightflag = otriequal(*searchtri, *bottommost);
  }
  *farright = farrightflag;
  return splayroot;
}
