gwy_delaunay_get_voronoi_cell(GwyDelaunayVertex *point, simplex *s0, GwyDelaunayMesh *m)
{
  simplex  *s;

  arrayList *neighbours = findNeighbours(point, s0);
  gint n = arrayListSize(neighbours);
  simplex  *simps[n];
  voronoiCell *vc;
  gint i, j = 0, done[3*n];
  GwyDelaunayVertex      *edges[3*n];
  GwyDelaunayVertex *v1, *v2, *v3;
  gint first, current, lastConsidered;
  gint match;


  if (n==0)
  {


      return NULL;
  }


  vc = newVoronoiCell(m,n);

  for (i=0; i<arrayListSize(neighbours); i++)
  {
    s = getFromArrayList(neighbours, i);
    getRemainingFace(s, point, &v1, &v2, &v3);


    simps[i]        = s;
    edges[3*i]      = v1;
    edges[3*i+1]    = v2;
    edges[3*i+2]    = v3;

    done[3*i]       = 0;
    done[3*i+1]     = 0;
    done[3*i+2]     = 0;


    circumCenter(s, vc->points[i]);
  }


  for (i=0; i<3*n; i++)
  {

    if (done[i]) continue;


    first   = i;
    current = i;
    lastConsidered = -1;


    do {
      match=0;
      for (j=0; j < 3*n; j++)
      {
        if (done[j]) continue;


        if ((edges[i] == edges[j]) && j != lastConsidered
                                   && isNeighbour(simps[current/3], simps[j/3]))
        {
          done[j] = 1;
          match   = 1;

          addVertexToVoronoiCell(vc, vc->points[j/3]);
          lastConsidered = current;
          current = j;
          break;
        }
      }
    } while (match && (current != first));

    startNewVoronoiFace(vc);
  }

  freeArrayList(neighbours, NULL);

  return vc;
}
