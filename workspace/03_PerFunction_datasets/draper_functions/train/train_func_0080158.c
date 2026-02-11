convert_spline_to_bezier(FILE *fh, int n, vertex *v)
{
  int i;
  vertex q0, q1, q2, q3;
  vertex u, w;

  for (i = 0; i < n - 3; i++ ) {
    thirdpoint(&q1, &v[i+1], &v[i+2]);
    thirdpoint(&q2, &v[i+2], &v[i+1]);
    thirdpoint(&u, &v[i+1], &v[i]);
    midpoint(&q0, &u, &q1);
    thirdpoint(&w, &v[i+2], &v[i+3]);
    midpoint(&q3, &w, &q2);
    if (i == 0)
      fprintf(fh, "\n%g %g m\n", q0.x, q0.y);
    fprintf(fh, "%g %g %g %g %g %g c\n", q1.x, q1.y, q2.x, q2.y, q3.x, q3.y);
  }
}
