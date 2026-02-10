static_export_seed (gamgi_cluster *cluster,
gamgi_polyhedron *polyhedron, int *n_polyhedrons, int *n_points,
gamgi_voronoi *voronoi)
{
if (polyhedron == NULL) return;

static_export_point (cluster, polyhedron->position, n_points);
*n_polyhedrons += 1;
}
