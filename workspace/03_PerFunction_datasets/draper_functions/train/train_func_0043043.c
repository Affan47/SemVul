cptWrite(FILE *fp, CPT cpt)
{
  char code[3] = {'B', 'F', 'N'};
  int n, k;
  int status = 0;

  for ( n = 0; n < cpt.ncolors; n++ )
    {
      fprintf(fp, "%g\t%d\t%d\t%d\t%g\t%d\t%d\t%d\n",
	     cpt.lut[n].z_low, cpt.lut[n].rgb_low[0], cpt.lut[n].rgb_low[1], cpt.lut[n].rgb_low[2],
	     cpt.lut[n].z_high, cpt.lut[n].rgb_high[0], cpt.lut[n].rgb_high[1], cpt.lut[n].rgb_high[2]);
    }

  for ( k = 0; k < 3; k++ )
    {
      if ( cpt.bfn[k].skip )
	fprintf(fp, "%c -\n", code[k]);
      else
	fprintf(fp, "%c\t%d\t%d\t%d\n", code[k], cpt.bfn[k].rgb[0], cpt.bfn[k].rgb[1], cpt.bfn[k].rgb[2]);
    }

  return (status);
}
