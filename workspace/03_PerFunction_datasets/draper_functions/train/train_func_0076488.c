AddContoursPovRay(FILE* file,Contours contours,gdouble Gap[], gdouble Color[])
{
	gint i;
	gint j;
	gint l;
	gint n=0;
	gint N[2] = {contours.N[0],contours.N[1]};
	PointsContour** pointscontour= contours.pointscontour;
	gdouble C1[3];
	gdouble C2[3];
	gchar* temp;

	for(i=1;i<N[0]-2;i++)
	{
		for(j=1;j<N[1]-2;j++)
		{
				for(n=0;n<pointscontour[i][j].N-1;n++)
				{
					for(l=0;l<3;l++) C1[l] = pointscontour[i][j].point[n].C[l] + Gap[l];
					for(l=0;l<3;l++) C2[l] = pointscontour[i][j].point[n+1].C[l] + Gap[l];
					temp = get_pov_cylingre(C1,C2,Color, 1.0);
					fprintf(file,"%s",temp);
					g_free(temp);
				}

		}
	}
}
