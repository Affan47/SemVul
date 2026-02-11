gamgi_mesa_render_polygons_color (int *loops,
double *points, int *paints, float *colors)
{
int i;
int n_loops, n_vertices;
double v1[3], v2[3], normal[3];

i = 0;
n_loops = loops[i++];
while (n_loops-- > 0)
  {


  if (paints[0] == i)
    { glColor3fv (colors); colors += 3; paints++; }


  glBegin (GL_POLYGON);

  n_vertices = loops[i++];

  gamgi_math_vector_sub (&points [3 * loops[i + 1]],
  &points [3 * loops[i]], v1);

  gamgi_math_vector_sub (&points [3 * loops[i + n_vertices - 1]],
  &points [3 * loops[i]], v2);

  gamgi_math_vector_cross (v1, v2, normal);
  glNormal3dv(normal);

  while (n_vertices-- > 0) glVertex3dv (&points [3 * loops[i++]]);

  glEnd ();
  }

glNormal3d (0.0, 0.0, 1.0);
}
