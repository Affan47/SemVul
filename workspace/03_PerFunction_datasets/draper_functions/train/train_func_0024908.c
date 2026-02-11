sinfo_kappa_sigma_CubeDataVector(
		int globalX,
		int globalY,
		CubeDataVector* pCubeDataVector,
		cpl_imagelist* imlistResult,
		cpl_imagelist** input_cubes,
		cpl_imagelist* sky_mask,
		int iPlanesNumber,
		int z_min,
		const double kappa,
		const double* exptimes
		)
{
	int plane = 0;
	int z = 0;


	cpl_array* pArray = 0;
	check_nomsg(pArray = cpl_array_new(pCubeDataVector->size, CPL_TYPE_DOUBLE));


	for (plane = z_min; plane < z_min + iPlanesNumber; plane++)
	{
		double val_msk = 0;
		int px = 0;
		cpl_image* imResult = 0;
		cpl_image* imMask = 0;
        double mask_adjustment = 0;
        int nValidPoints = 0;
		cpl_array_fill_window_invalid(pArray, 0, pCubeDataVector->size);
		check_nomsg(imMask = cpl_imagelist_get(sky_mask, plane - z_min));
		check_nomsg(val_msk = cpl_image_get(imMask, globalX, globalY, &px));
		for (z = 0; z < pCubeDataVector->size; z++)
		{

			cpl_imagelist* pCube = 0;
			CubeData* pCubeData = pCubeDataVector->pdata[z];
			pCube = input_cubes[pCubeData->iCubeNumber];
			if (pCube)
			{
				cpl_image* pImage = cpl_imagelist_get(pCube, plane - z_min);

				if (pImage)
				{
					int is_rejected = 0;
					double value = 0;
					check_nomsg(value = cpl_image_get(pImage, pCubeData->iLocalX,
					                pCubeData->iLocalY, &is_rejected));
					if (!isnan(value))
					{
						check_nomsg(cpl_array_set(pArray, z, value));
						++nValidPoints;
                    }
					else
					{
						mask_adjustment += exptimes[z];
					}
				}
				else
				{
					sinfo_msg("pImage is null");
				}
			}
		}
		if(nValidPoints)
		{
		   sinfo_kappa_sigma_array_with_mask(pArray, pCubeDataVector->size,
		                   kappa, imMask, exptimes, globalX, globalY,
		                   mask_adjustment);
		   check_nomsg(imResult = cpl_imagelist_get(imlistResult, plane));
		   if (imResult)
		   {
			  check_nomsg(cpl_image_set(imResult, globalX, globalY,
			                  cpl_array_get_mean(pArray)));
		   }
		   else
		   {
			  sinfo_msg("imResult is null");
		   }
		} else
		{

			check_nomsg(cpl_image_set(imMask, globalX,globalY, 0));
		}
    }
	for (z = 0; z < pCubeDataVector->size; z++)
	{
		CubeData* pCubeData = pCubeDataVector->pdata[z];
		cpl_free(pCubeData);
	}
	cpl_array_delete(pArray);
	return;
	cleanup:

	return;
}
