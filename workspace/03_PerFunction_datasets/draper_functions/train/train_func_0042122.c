changepen(pentype pen)
{
  Char picthi, pictlo;
  long  pictint;
  lastpen = pen;

 switch (pen) {

  case treepen:
    linewidth = treeline;
    if (plotter == hp)
      fprintf(plotfile, "SP1;\n");
    if (plotter == lw) {
      fprintf(plotfile, "stroke %8.2f setlinewidth \n", treeline);
      fprintf(plotfile, " 1 setlinecap 1 setlinejoin \n");
    }
#ifdef WIN32
    if (plotter == winpreview)
      SelectObject(hdc, hPenTree);
#endif
    break;

  case labelpen:
    linewidth = labelline;
    if (plotter == hp)
      fprintf(plotfile, "SP2;\n");
    if (plotter == lw) {
      fprintf(plotfile, " stroke%8.2f setlinewidth \n", labelline);
      fprintf(plotfile, "1 setlinecap 1 setlinejoin \n");
    }
#ifdef WIN32
    if (plotter == winpreview)
      SelectObject(hdc, hPenLabel);
#endif
    break;
  }
#ifdef MAC
if (plotter == mac){
      pictint = ( long)(linewidth + 0.5);
      if (pictint ==0)
           pictint = 1;
}
#endif

  if (plotter != pict)
    return;
  pictint = ( long)(linewidth + 0.5);
  if (pictint == 0)
    pictint = 1;
  picthi = (Char)(pictint / 256);
  pictlo = (Char)(pictint & 255);
  fprintf(plotfile, "\007%c%c%c%c", picthi, pictlo, picthi, pictlo);
  bytewrite += 5;
}
