mpixel (header *hd)
{	double x,y;
	hd=new_matrix(1,2,""); if (error) return;
	getpixelsize(&x,&y);
	x*=(x_max-x_min)/(lowerc-upperc);
	y*=(y_max-y_min)/(lowerr-upperr);
	*(matrixof(hd))=x; *(matrixof(hd)+1)=y;
}
