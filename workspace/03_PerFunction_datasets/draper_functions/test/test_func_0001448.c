gamgi_math_polygon_length_lines (int *lines, double *points)
{
double sub[3];
double length;
int vertex1, vertex2;
int i, n_lines;


i = 0;
n_lines = lines[i++];

length = 0.0;
while (n_lines-- > 0)
  {
  vertex1 = 3 * lines[i++];
  vertex2 = 3 * lines[i++];
  gamgi_math_vector_sub (points + vertex1, points + vertex2, sub);
  length += gamgi_math_vector_length (sub);
  }

return length;
}
