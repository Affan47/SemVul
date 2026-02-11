static_conflict_recreate (int f, int e, int v,
static_polytope *polytope)
{
static_edge *edge;
static_vertex *vertex;
int f_start, f_end;
int v_start, v_end;
int n_conflicts;
int i;

edge = polytope->edges[e];


f_start = edge->f_start;
f_end = edge->f_end;

v_start = edge->v_start;
v_end = edge->v_end;


n_conflicts = 0;
n_conflicts += static_conflict_retrieve (f, f_start, v_start, v_end, v, polytope);
n_conflicts += static_conflict_retrieve (f, f_end, v_start, v_end, v, polytope);


if (polytope->id == INT_MAX)
  {
  polytope->id = 0;
  for (i = v; i < polytope->n_neighbours; i++)
    { vertex = polytope->vertices[i]; vertex->id = -1; }
  }
else polytope->id += 1;

return n_conflicts;
}
