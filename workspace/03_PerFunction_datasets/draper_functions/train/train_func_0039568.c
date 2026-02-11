static_raw_x1y0 (int cell_x, int cell_y, int cell_z,
int shell, static_polytope *polytope)
{
int n, n_x, n_y, n_z;
int i;

n = polytope->n_cells;


n_x = shell + cell_x;
if (n_x < 0 || n_x > n - 1) return;

n_y = -shell + cell_y;
if (n_y < 0 || n_y > n - 1) return;

for (i = -shell + 1; i <= shell - 1; i++)
  {
  n_z = i + cell_z;
  if (n_z < 0 || n_z > n - 1) continue;

  if (static_inside_local (shell, -shell, i, polytope) == TRUE)
    static_neighbour_get (n_x, n_y, n_z, polytope);
  }
}
