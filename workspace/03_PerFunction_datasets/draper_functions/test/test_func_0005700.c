buildVoronoiDiagram(
			float		threshold,
			float		robot_size,
			int			x1,
			int			x2,
			int			y1,
			int			y2)
{

	if (!x1 && !x2 && !y1 && !y2) {
		x1=y1=0;
		x2=size_x-1;
		y2=size_y-1;
	}
	else {
		x1=max(0,x1);
		y1=max(0,y1);
		x2=min(x2,static_cast<int>(size_x)-1);
		y2=min(y2,static_cast<int>(size_y)-1);
	}

	int robot_size_units= round(100*robot_size / resolution);


	m_voronoi_diagram.setSize(x_min,x_max, y_min,y_max, resolution);
	ASSERT_EQUAL_(m_voronoi_diagram.getSizeX(), size_x);
	ASSERT_EQUAL_(m_voronoi_diagram.getSizeY(), size_y);
	m_voronoi_diagram.fill(0);


	voroni_free_threshold= 1.0f - threshold;

	int     basis_x[2],basis_y[2];
	int     nBasis;


	for (int x=x1;x<=x2;x++) {
		for (int y=y1;y<=y2;y++)
		{
			const int Clearance = computeClearance(x,y,basis_x,basis_y,&nBasis);

			if (Clearance > robot_size_units )
				setVoroniClearance(x,y,Clearance );
		}
	}


	int    nDiag;
	for (int x=x1;x<=x2;x++) {
		for (int y=y1;y<=y2;y++) {
			if ( getVoroniClearance(x,y) )
			{
				nDiag=0;
				for (int xx=x-1;xx<=(x+1);xx++)
					for (int yy=y-1;yy<=(y+1);yy++)
						if (getVoroniClearance(xx,yy)) nDiag++;


				if (nDiag>3)
					setVoroniClearance(x,y,0);
			}
		}
	}
}
