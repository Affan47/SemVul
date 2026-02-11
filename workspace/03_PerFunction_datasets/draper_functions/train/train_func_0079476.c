cbf_get_inferred_pixel_size (cbf_detector detector,
                                               int axis_number,
                                               double *psize)
{

  if (axis_number < 0) axis_number = detector->axes+1+axis_number;

  if (!detector || axis_number < 1 || detector-> axes < axis_number )

    return CBF_ARGUMENT;


  *psize = fabs( (detector-> increment)[axis_number-1] );

  return 0;

}
