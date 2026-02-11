emitGraph (FILE* fp, maze* mp, int n_edges, route* route_list, epair_t es[])
{
    int i;
    boxf bb, absbb;
    box bbox;

    absbb.LL.x = absbb.LL.y = MAXDOUBLE;
    absbb.UR.x = absbb.UR.y = -MAXDOUBLE;

    fprintf (fp, "%s", prolog2);
    fprintf (fp, "%d %d translate\n", TRANS, TRANS);

    fputs ("0 0 1 setrgbcolor\n", fp);
    for (i = 0; i < mp->ngcells; i++) {
      bb = mp->gcells[i].bb;
      fprintf (fp, "%f %f %f %f node\n", bb.LL.x, bb.LL.y, bb.UR.x, bb.UR.y);
    }

    for (i = 0; i < n_edges; i++) {
	absbb = emitEdge (fp, es[i].e, route_list[i], mp, i, absbb);
    }

    fputs ("0.8 0.8 0.8 setrgbcolor\n", fp);
    for (i = 0; i < mp->ncells; i++) {
      bb = mp->cells[i].bb;
      fprintf (fp, "%f %f %f %f cell\n", bb.LL.x, bb.LL.y, bb.UR.x, bb.UR.y);
      absbb.LL.x = MIN(absbb.LL.x, bb.LL.x);
      absbb.LL.y = MIN(absbb.LL.y, bb.LL.y);
      absbb.UR.x = MAX(absbb.UR.x, bb.UR.x);
      absbb.UR.y = MAX(absbb.UR.y, bb.UR.y);
    }

    bbox.LL.x = absbb.LL.x + TRANS;
    bbox.LL.y = absbb.LL.y + TRANS;
    bbox.UR.x = absbb.UR.x + TRANS;
    bbox.UR.y = absbb.UR.y + TRANS;
    fprintf (fp, epilog2, bbox.LL.x, bbox.LL.y,  bbox.UR.x, bbox.UR.y);
}
