plot_image_get_percentile(plot_args_t* pargs, plotimage_t* args,
							   double percentile,
							   unsigned char* rgb) {
	int j;
	int N;
	int I;
	if (percentile < 0.0 || percentile > 1.0) {
		ERROR("percentile must be between 0 and 1 (ok, so it's badly named, sue me)");
		return -1;
	}

	if (!args->img) {
		if (plot_image_read(pargs, args)) {
			ERROR("Failed to read image file: can't get percentile!\n");
			return -1;
		}
	}

	N = args->W * args->H;
	I = MAX(0, MIN(N-1, floor(N * percentile)));
	for (j=0; j<3; j++) {
		int* P;
		P = permuted_sort(args->img + j, 4, compare_uchars_asc, NULL, N);
		rgb[j] = args->img[4 * P[I] + j];
		free(P);
	}
	return 0;
}
