touser(float x, float y, float z, float *uux, float *uuy) {
	float uz,ux,uy,p,q;
	ux = image[0][0]*x + image[0][1]*y + image[0][2]*z + image[0][3];
	uy = image[1][0]*x + image[1][1]*y + image[1][2]*z + image[1][3];
	uz = image[2][0]*x + image[2][1]*y + image[2][2]*z + image[2][3];

	ux -= eye_x;
	uy -= eye_y;
	if (maxdepth!=0) {
		p = vdist;
		q = uz/maxdepth;
		ux = ux - ux*p*q/(1-p+p*q);
		uy = uy - uy*p*q/(1-p+p*q);


	}
	*uux = ux + eye_x;
	*uuy = uy + eye_y;
}
