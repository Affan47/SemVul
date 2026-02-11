test_unit() {
	int i,j;
	gunit = true;
	for (i=0;i<3;i++) for (j=0;j<3;j++) if (i!=j) if(g.image[i][j]!=0.0) gunit = false;
	for (i=0;i<3;i++) if (g.image[i][i]!=1.0) gunit = false;
}
