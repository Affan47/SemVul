psdrawellipse(GtkPlotPC *pc,
              gboolean filled,
              gdouble x, gdouble y,
              gdouble width, gdouble height)
{
  FILE *psout = GTK_PLOT_PS(pc)->psfile;

  fprintf(psout,"n %g %g %g %g 0 360 ellipse\n",
          x+width/2., y+height/2.,
          width/2., height/2.);

  if(filled)
     fprintf(psout,"f\n");

  fprintf(psout,"s\n");
}
