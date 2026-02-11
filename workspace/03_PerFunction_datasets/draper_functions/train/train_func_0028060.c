edge_gradient(char const * const output_fn, int threshold = 0) const{
	int h, i, j;
	double **dx, **dy, **dE = edge_gradient(dx, dy);
	png_bytep *result = new png_bytep[height];
	normalize(width, height, dE);
	if (!threshold){
		for (i = 0; i < height; ++i){
			result[i] = new png_byte[rowbytes];
			for (j = 0; j < width; ++j){
				for (h = 0; h < pixel_size; ++h){
					result[i][j * pixel_size + h] = dE[i][j];
				}
			}
		}
	}else{
		for (i = 0; i < height; ++i){
			for (j = 0; j < rowbytes; ++j){
				for (h = 0; h < pixel_size; ++h){
					result[i][j * pixel_size + h] = dE[i][j] >= threshold ? 0 : 255;
				}
			}
		}
	}
	write_png_file(output_fn, result);
	delete_2d_array<double>(height, dx);
	delete_2d_array<double>(height, dy);
	delete_2d_array<double>(height, dE);
	delete_2d_array<png_byte>(height, result);
}
