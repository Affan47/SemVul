read_fits_size(plotimage_t* args, int* W, int* H) {
    anqfits_t* anq;
    const anqfits_image_t* img;
    anq = anqfits_open(args->fn);
    if (!anq) {
		ERROR("Failed to read input file: \"%s\"", args->fn);
        return -1;
    }
    img = anqfits_get_image_const(anq, args->fitsext);
    if (!img) {
        ERROR("Failed to read image extension %i from file \"%s\"\n",
              args->fitsext, args->fn);
        anqfits_close(anq);
        return -1;
    }
	if (W)
		*W = img->width;
	if (H)
		*H = img->height;
    if (args->fitsplane >= img->planes) {
        ERROR("Requested FITS image plane %i, but only %i available\n",
              args->fitsplane, (int)img->planes);
        anqfits_close(anq);
        return -1;
    }
    anqfits_close(anq);
	return 0;
}
