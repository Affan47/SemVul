gabedit_contoursplot_get_range (GabeditContoursPlot *contoursplot, gdouble *xmin, gdouble *xmax, gdouble *ymin, gdouble *ymax)
{
  g_return_if_fail (contoursplot != NULL);
  g_return_if_fail (GABEDIT_IS_ContoursPLOT (contoursplot));

  if (xmin!=NULL)
    *xmin=contoursplot->xmin;
  if (xmax!=NULL)
    *xmax=contoursplot->xmax;
  if (ymax!=NULL)
    *ymax=contoursplot->ymax;
  if (ymin!=NULL)
    *ymin=contoursplot->ymin;
}
