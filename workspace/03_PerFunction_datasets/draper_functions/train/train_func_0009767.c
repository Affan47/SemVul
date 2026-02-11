MGPS_epoly(CPoint3 *pts, int num, int *col,
		double ewidth, int *ecol)
{
    int i;

    fprintf(psout, "%g ", ewidth);
    fprintf(psout, "%g %g %g ", ecol[0]/255.0, ecol[1]/255.0, ecol[2]/255.0);
    for (i=0; i<num; i++)
	fprintf(psout, "%g %g ", pts[i].x, pts[i].y);
    fprintf(psout, "%g %g %g ", col[0]/255.0, col[1]/255.0, col[2]/255.0);
    fprintf(psout, "epoly\n");
}
