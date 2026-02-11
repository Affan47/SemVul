sinfo_atmo_apply_cube_polynomial_shift(
		cpl_polynomial* poly,
		cpl_imagelist* pCube,
		double lambda0,
		double airmass,
		double parallactic,
		double pixelsz,
		int centpix)
{
	cpl_imagelist* retcube = NULL;
	cpl_error_code 	err = CPL_ERROR_NONE;
	cpl_vector* vparams = NULL;
	double * kernel = sinfo_generate_interpolation_kernel("default");
	int cubesize = 0;
	int i = 0;


	double l0_shift_x = 0;
	double l0_shift_y = 0;

	vparams = cpl_vector_new(2);
	cpl_vector_set(vparams, 0, airmass);
	cpl_vector_set(vparams, 1, lambda0);
	err = cpl_error_get_code();
	if (err == CPL_ERROR_NONE)
	{
		l0_shift_y = cpl_polynomial_eval(poly, vparams);
		l0_shift_x = 0;

		sinfo_atmo_rotate_point(&l0_shift_x, &l0_shift_y, parallactic);
		cubesize = cpl_imagelist_get_size(pCube);
		err =  cpl_error_get_code();
	}
	if (err == CPL_ERROR_NONE)
	{
		retcube = cpl_imagelist_new();
		for (i = 0; i < cubesize; i++)
		{

			double lambda = lambda0 - (centpix - i) * pixelsz;
			double shift_y = 0;
			double shift_x = 0;

			cpl_vector_set(vparams, 1, lambda);

			shift_y = cpl_polynomial_eval(poly, vparams);
			err = cpl_error_get_code();
			if (err == CPL_ERROR_NONE)
			{
				double res_shift_x = -(shift_x - l0_shift_x);
				double res_shift_y = -(shift_y - l0_shift_y);
				cpl_image* plane = NULL;
				cpl_image* pimresult = NULL;

				sinfo_atmo_rotate_point(&res_shift_x, &res_shift_y, parallactic);
				plane = cpl_imagelist_get(pCube, i);
				pimresult = sinfo_new_shift_image(
						plane,
						res_shift_x,
						res_shift_y,
						kernel);
				if (err == CPL_ERROR_NONE)
				{
					err = cpl_imagelist_set(retcube, pimresult, i);
				}
				else
				{
					sinfo_msg_error("Error sinfo_new_shift_image, %s",
										cpl_error_get_where());
				}
				if (err != CPL_ERROR_NONE)
					break;
			}
			else
			{
				sinfo_msg_error("Error polynomial_eval, %s",
						cpl_error_get_where());
			}
			if (err != CPL_ERROR_NONE)
				break;
		}
	}
	if (err != CPL_ERROR_NONE)
	{
		sinfo_free_imagelist(&retcube);
		sinfo_msg_error("Error during shift planes in the cube, %s",
				cpl_error_get_where());
	}
    sinfoni_free_vector(&vparams);
	cpl_free(kernel);
	return retcube;
}
