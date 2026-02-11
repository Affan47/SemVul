gfs_time_write (GfsTime * t, FILE * fp)
{
  g_return_if_fail (t != NULL);
  g_return_if_fail (fp != NULL);

  fprintf (fp, "{ i = %u t = %g ", t->i, t->t);
  if (t->start != 0.)
    fprintf (fp, "start = %g ", t->start);
  if (t->istart != 0)
    fprintf (fp, "start = %u ", t->istart);
  if (t->end < G_MAXDOUBLE)
    fprintf (fp, "end = %g ", t->end);
  if (t->iend < G_MAXINT)
    fprintf (fp, "iend = %u ", t->iend);
  if (t->dtmax < G_MAXDOUBLE)
    fprintf (fp, "dtmax = %g ", t->dtmax);
  fputc ('}', fp);
}
