static_export_color (gamgi_cluster *cluster,
float *color, int n_loops, int n_polyhedrons)
{


if (n_polyhedrons + 1 > cluster->n_colors)
  {
  cluster->n_colors += GAMGI_PHYS_VORONOI_ARRAY;
  cluster->colors = (float *) realloc (cluster->colors,
  3 * cluster->n_colors * sizeof (float));

  cluster->n_paints += GAMGI_PHYS_VORONOI_ARRAY;
  cluster->paints = (int *) realloc (cluster->paints,
  cluster->n_paints * sizeof (int));
  }


cluster->colors[3 * n_polyhedrons + 0] = color[0];
cluster->colors[3 * n_polyhedrons + 1] = color[1];
cluster->colors[3 * n_polyhedrons + 2] = color[2];
cluster->paints[n_polyhedrons] = n_loops;
}
