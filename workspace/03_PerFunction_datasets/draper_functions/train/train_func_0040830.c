removebox(struct mesh *m, struct behavior *b)
#else
long removebox(m, b)
struct mesh *m;
struct behavior *b;
#endif

{
  struct otri deadtriangle;
  struct otri searchedge;
  struct otri checkedge;
  struct otri nextedge, finaledge, dissolveedge;
  vertex markorg;
  long hullsize;
  triangle ptr;

  if (b->verbose) {
    printf("  Removing triangular bounding box.\n");
  }

  nextedge.tri = m->dummytri;
  nextedge.orient = 0;
  symself(nextedge);

  lprev(nextedge, finaledge);
  lnextself(nextedge);
  symself(nextedge);


  lprev(nextedge, searchedge);
  symself(searchedge);


  lnext(nextedge, checkedge);
  symself(checkedge);
  if (checkedge.tri == m->dummytri) {


    lprevself(searchedge);
    symself(searchedge);
  }


  m->dummytri[0] = encode(searchedge);
  hullsize = -2l;
  while (!otriequal(nextedge, finaledge)) {
    hullsize++;
    lprev(nextedge, dissolveedge);
    symself(dissolveedge);


    if (!b->poly) {


      if (dissolveedge.tri != m->dummytri) {
        org(dissolveedge, markorg);
        if (vertexmark(markorg) == 0) {
          setvertexmark(markorg, 1);
        }
      }
    }

    dissolve(dissolveedge);
    lnext(nextedge, deadtriangle);
    sym(deadtriangle, nextedge);

    triangledealloc(m, deadtriangle.tri);

    if (nextedge.tri == m->dummytri) {

      otricopy(dissolveedge, nextedge);
    }
  }
  triangledealloc(m, finaledge.tri);

  trifree((void *) m->infvertex1);
  trifree((void *) m->infvertex2);
  trifree((void *) m->infvertex3);

  return hullsize;
}
