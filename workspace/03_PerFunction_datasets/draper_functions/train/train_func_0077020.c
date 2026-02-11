static_measure_vertices (int *real,
int *border, int *total, gamgi_voronoi *voronoi)
{
gamgi_polyhedron *polyhedron;
gamgi_vertex *vertex;
gamgi_slist *slist_v;
int n_seeds, i;

*real = 0;
*border = 0;
*total = 0;


n_seeds = voronoi->n_seeds;
for (i = 0; i < n_seeds; i++)
  {
  polyhedron = voronoi->polyhedron[i];
  if (polyhedron == NULL) continue;

  for (slist_v = polyhedron->vertex; slist_v != NULL; slist_v = slist_v->next)
    {
    vertex = (gamgi_vertex *) slist_v->data;


    if (vertex->vertex != NULL) continue;
    if (vertex->last == NULL) *real += 1;
    else *border += 1;
    }
  }

*total = *real + *border;
}
