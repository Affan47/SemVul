static_pbc_x0y1z1 (int cell_x, int cell_y, int cell_z,
double *position0, double radius0, int mark, int shell,
double *borders, double *width, gamgi_voronoi *voronoi)
{
gamgi_slist *slist;
double position1[3], shift[3];
double radius1, size;
int n, n_x, n_y, n_z;
int local, global;
int index;

n = voronoi->n_cells;


size = voronoi->size;
if (borders[0] > size) return;
if (borders[3] > size) return;
if (borders[5] > size) return;

n_x = -shell + cell_x;
if (n_x < -n || n_x > 2*n - 1) return;

static_pbc (n, width[0], &n_x, &shift[0]);

n_y = shell + cell_y;
if (n_y < -n || n_y > 2*n - 1) return;

static_pbc (n, width[1], &n_y, &shift[1]);

n_z = shell + cell_z;
if (n_z < -n || n_z > 2*n - 1) return;

static_pbc (n, width[2], &n_z, &shift[2]);

index = n_z * n * n + n_y * n + n_x;
for (slist = voronoi->cells[index]; slist != NULL; slist = slist->next)
  {
  static_neighbour_pbc (slist, shift, position0,
  position1, &radius1, &local, &global);
  static_neighbour_try (position0, radius0, mark,
  position1, radius1, local, global, voronoi);
  }
}
