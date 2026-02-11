convolve (lpyramid_t *pyramid, float *a, float *b)

{
    int y,x,i,j,nx,ny;
    const float Kernel[] = {0.05f, 0.25f, 0.4f, 0.25f, 0.05f};
    int width = pyramid->width;
    int height = pyramid->height;

    for (y=0; y<height; y++) {
	for (x=0; x<width; x++) {
	    int index = y * width + x;
	    a[index] = 0.0f;
	    for (i=-2; i<=2; i++) {
		for (j=-2; j<=2; j++) {
		    nx=x+i;
		    ny=y+j;
		    if (nx<0) nx=-nx;
		    if (ny<0) ny=-ny;
		    if (nx>=width) nx=2*(width-1)-nx;
		    if (ny>=height) ny=2*(height-1)-ny;
		    a[index] += Kernel[i+2] * Kernel[j+2] * b[ny * width + nx];
		}
	    }
	}
    }
}
