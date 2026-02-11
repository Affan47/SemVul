gfs_event_harmonic_write (GtsObject * o, FILE * fp)
{
  GfsEventHarmonic * s = GFS_EVENT_HARMONIC (o);
  guint i, j;

  (* GTS_OBJECT_CLASS (gfs_event_harmonic_class ())->parent_class->write) (o, fp);

  fprintf (fp, " %s %s %s %s", s->v->name, s->Aname, s->Bname, s->z->name);
  if (s->e)
    fprintf (fp, " %s", s->e->name);
  for (i = 0; i < s->omega->len; i++)
    fprintf (fp, " %.12lf", g_array_index (s->omega, gdouble, i));
  fprintf (fp, " { %d", s->invertible);
  for (i = 0; i < 2*s->omega->len + 1; i++)
    for (j = 0; j < 2*s->omega->len + 1; j++)
      fprintf (fp, " %.12lf", s->M[i][j]);
  fputs (" }", fp);
}
