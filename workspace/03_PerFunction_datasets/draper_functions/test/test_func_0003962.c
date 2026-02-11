gamgi_math_polygon_check_colors (int *loops,
int n_loops, float *colors, int n_colors, int *paints, int n_paints)
{
int n_faces, i;


if (n_loops == 0) return TRUE;


n_faces = loops[0];
if (n_colors < 1 || n_colors > n_faces) return FALSE;
if (n_paints != n_colors + 1) return FALSE;


for (i = 0; i < 3 * n_colors; i++)
  if (colors[i] < 0.0 || colors[i] > 1.0) return FALSE;


for (i = 0; i < n_colors; i++)
  if (paints[i] <= 0 || paints[0] >= n_loops) return FALSE;
if (paints[n_colors] != 0) return FALSE;

return TRUE;
}
