SortEdges (void)
{
  if (_need_edges_sorting == false) {
    return;
  }
  _need_edges_sorting = false;

  edge_list *list = (edge_list *) g_malloc(numberOfEdges() * sizeof (edge_list));
  for (int p = 0; p < numberOfPoints(); p++)
    {
      int const d = getPoint(p).totalDegree();
      if (d > 1)
        {
          int cb;
          cb = getPoint(p).incidentEdge[FIRST];
          int nb = 0;
          while (cb >= 0)
            {
              int n = nb++;
              list[n].no = cb;
              if (getEdge(cb).st == p)
                {
                  list[n].x = getEdge(cb).dx;
                  list[n].starting = true;
                }
              else
                {
                  list[n].x = -getEdge(cb).dx;
                  list[n].starting = false;
                }
              cb = NextAt (p, cb);
            }
          SortEdgesList (list, 0, nb - 1);
          _pts[p].incidentEdge[FIRST] = list[0].no;
          _pts[p].incidentEdge[LAST] = list[nb - 1].no;
          for (int i = 0; i < nb; i++)
            {
              if (list[i].starting)
                {
                  if (i > 0)
                    {
                      _aretes[list[i].no].prevS = list[i - 1].no;
                    }
                  else
                    {
                      _aretes[list[i].no].prevS = -1;
                    }
                  if (i < nb - 1)
                    {
                      _aretes[list[i].no].nextS = list[i + 1].no;
                    }
                  else
                    {
                      _aretes[list[i].no].nextS = -1;
                    }
                }
              else
                {
                  if (i > 0)
                    {
                      _aretes[list[i].no].prevE = list[i - 1].no;
                    }
                  else
                    {
                      _aretes[list[i].no].prevE = -1;
                    }
                  if (i < nb - 1)
                    {
                      _aretes[list[i].no].nextE = list[i + 1].no;
                    }
                  else
                    {
                      _aretes[list[i].no].nextE = -1;
                    }
                }
            }
        }
    }
  g_free(list);
}
