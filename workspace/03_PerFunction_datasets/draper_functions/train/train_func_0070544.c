applySquareCube()
{
	gint i, j, k;
	gboolean beg = TRUE;
	gdouble v;
	gdouble scal;

	TypeGrid = GABEDIT_TYPEGRID_EDENSITY;
	progress_orb(0,GABEDIT_PROGORB_SCALEGRID,TRUE);
	scal = (gdouble)1.01/grid->N[0];
	for(i=0;i<grid->N[0];i++)
	{
		for(j=0;j<grid->N[1];j++)
		{
			for(k=0;k<grid->N[2];k++)
			{
				grid->point[i][j][k].C[3] = grid->point[i][j][k].C[3]*grid->point[i][j][k].C[3];
				v = grid->point[i][j][k].C[3];
				if(beg)
				{
					beg = FALSE;
        				grid->limits.MinMax[0][3] =  v;
        				grid->limits.MinMax[1][3] =  v;
				}
                		else
				{
        				if(grid->limits.MinMax[0][3]>v)
        					grid->limits.MinMax[0][3] =  v;
        				if(grid->limits.MinMax[1][3]<v)
        					grid->limits.MinMax[1][3] =  v;
				}
			}
		}
		if(CancelCalcul)
		{
			progress_orb(0,GABEDIT_PROGORB_SCALEGRID,TRUE);
			break;
		}
		progress_orb(scal,GABEDIT_PROGORB_SCALEGRID,FALSE);
	}
	progress_orb(0,GABEDIT_PROGORB_SCALEGRID,TRUE);
	if(CancelCalcul) grid = free_grid(grid);
	else
	{
		limits = grid->limits;
	}
}
