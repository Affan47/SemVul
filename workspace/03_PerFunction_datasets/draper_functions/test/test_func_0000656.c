static_scan_vertices (gamgi_voronoi *voronoi)
{
gamgi_polyhedron *polyhedron;
gamgi_face *face;
gamgi_vertex *vertex;
gamgi_slist *slist_v, *slist_f;
int n_seeds, i;

n_seeds = voronoi->n_seeds;


for (i = 0; i < n_seeds; i++)
  {
  polyhedron = voronoi->polyhedron[i];
  if (polyhedron == NULL) continue;

  for (slist_v = polyhedron->vertex; slist_v != NULL; slist_v = slist_v->next)
    {
    vertex = (gamgi_vertex *) slist_v->data;
    vertex = static_vertex (vertex);
    vertex->last = NULL;
    }
  }


for (i = 0; i < n_seeds; i++)
  {
  polyhedron = voronoi->polyhedron[i];
  if (polyhedron == NULL) continue;

  for (slist_f = polyhedron->face; slist_f != NULL; slist_f = slist_f->next)
    {
    face = (gamgi_face *) slist_f->data;
    if (face->area < voronoi->area) continue;

    for (slist_v = face->vertex; slist_v != NULL; slist_v = slist_v->next)
      {


      vertex = (gamgi_vertex *) slist_v->data;
      vertex = static_vertex (vertex);
      if (face->local < 0 || face->global != 0 ||
      voronoi->polyhedron[face->local] == NULL)
        vertex->last = vertex;
      }
    }
  }

}
