updateCell(int x,int y, float v)
{

	if (static_cast<unsigned int>(x)>=size_x || static_cast<unsigned int>(y)>=size_y)
		return;


	cellType	&theCell = map[x+y*size_x];


	if ( updateInfoChangeOnly.enabled )
	{
		float	old	= l2p(theCell);
		float		new_v	= 1 / ( 1 + (1-v)*(1-old)/(old*v) );
		updateInfoChangeOnly.cellsUpdated++;
		updateInfoChangeOnly.I_change+= 1-(H(new_v)+H(1-new_v))/MAX_H;
	}
	else
	{
		cellType obs = p2l(v);
		if (obs>0)
		{
			if ( theCell>(OCCGRID_CELLTYPE_MAX-obs) )
					theCell = OCCGRID_CELLTYPE_MAX;
			else	theCell += obs;
		}
		else
		{
			if ( theCell<(OCCGRID_CELLTYPE_MIN-obs) )
					theCell = OCCGRID_CELLTYPE_MIN;
			else	theCell += obs;
		}
	}
}
