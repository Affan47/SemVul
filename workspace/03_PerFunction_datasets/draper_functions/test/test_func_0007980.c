irplib_hist_fill(irplib_hist     * hist,
                 const cpl_image * image)
{
    double           binwidth = 1.0;
    int              nsamples;
    int              i;
    const float    * data = 0;
    const cpl_binary*  bpm_data = 0;
    const cpl_mask* bpm = 0;
    cpl_error_code   error;


    cpl_ensure_code(hist  != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(image != NULL, CPL_ERROR_NULL_INPUT);

    if (hist -> bins == NULL) {
	const double        hstart = cpl_image_get_min(image);
	const double        hrange = cpl_image_get_max(image) - hstart;


	const unsigned long nbins  = (unsigned long) (hrange / binwidth) + 2;

	error = irplib_hist_init(hist, nbins, hstart, hrange);
	cpl_ensure_code(!error, error);
    } else {
	cpl_ensure_code(hist -> range > 0, CPL_ERROR_ILLEGAL_INPUT);


        binwidth = hist -> range / (double)(hist -> nbins - 2);
    }

    nsamples = cpl_image_get_size_x(image) * cpl_image_get_size_y(image);
    data     = cpl_image_get_data_float_const(image);
    bpm 	 = cpl_image_get_bpm_const(image);
    if (bpm)
    {
    	bpm_data 	 = cpl_mask_get_data_const(bpm);
    }

    for (i = 0; i < nsamples; i++)
    {
    	int pos = 0;
        if(bpm_data && bpm_data[i] != CPL_BINARY_0)
    	{
    		continue;
    	}
		pos = (int)((data[i] - hist -> start) / binwidth);
		if (pos <  0)
		{
			hist -> bins[0]++;
		} else if ((unsigned long) pos >= (hist -> nbins - 2))
		{
			hist -> bins[hist -> nbins - 1]++;
		} else
		{
			hist -> bins[pos + 1]++;
		}
    }

    return cpl_error_get_code();
}
