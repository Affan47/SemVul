hdrl_mirror_edges(cpl_image *image, int dx, int dy)
{

	int xx = 0;
	int yy = 0;
	int xs = 0;
	int ys = 0;
	int inrow = 1;
	int outrow = 1;
	int i =0;
	int j = 0;

	float *data;
	float *out_data;


	cpl_image 	*big_image;


	xs = cpl_image_get_size_x(image);
	ys = cpl_image_get_size_y(image);

	xx = xs+(2*dx);
	yy = ys+(2*dy);

	data = cpl_image_get_data_float(image);

	big_image = cpl_image_new(xx, yy, CPL_TYPE_FLOAT);
	out_data = cpl_image_get_data_float(big_image);

	for (j=0; j<ys ; j++){
		inrow = j*xs;
		outrow = (j+dy)*xx;

		for (i=0; i<xs ; i++){
			out_data[outrow+dx+i] = data[inrow+i];
		}

		for (i=0; i<dx; i++){
			out_data[outrow+i] = data[inrow+dx-i-1];
			out_data[outrow+xs+dx+i] = data[inrow+xs-i-1];

		}
	}

	for (j=0; j<dy ; j++) {

		for (i=0; i<xx; i++) {
			out_data[j*xx+i] = out_data[(2*dy-j-1)*xx+i];
			out_data[(yy-j-1)*xx+i] = out_data[(yy-2*dy+j)*xx+i];
		}
	}

	return big_image;
}
