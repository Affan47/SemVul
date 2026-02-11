xsh_imagelist_collapse_median_create(cpl_imagelist* iml)
{

   int sx=0;
   int sy=0;
   int nimg=0;
   cpl_image* img=NULL;
   cpl_array* values=NULL;

   float **pdata = NULL;
   cpl_binary ** pbinary = NULL;

   int i=0;
   cpl_size k=0;
   int count=0;
   int sx_sy=0;

   float* pima=NULL;

   cpl_image* result=NULL;


   XSH_ASSURE_NOT_NULL_MSG(iml, "Null input imagelist");

   nimg=cpl_imagelist_get_size(iml);
   if(nimg>0) {
      img=cpl_imagelist_get(iml,0);
   }
   sx=cpl_image_get_size_x(img);
   sy=cpl_image_get_size_y(img);
   sx_sy=sx*sy;


   pdata = cpl_malloc (nimg * sizeof (float *));
   assure (pdata != NULL, cpl_error_get_code (),
           "Cant allocate memory for data pointers");


   pbinary = cpl_malloc (nimg * sizeof (cpl_binary *));
   assure (pbinary != NULL, cpl_error_get_code (),
           "Cant allocate memory for binary pointers");


   for (k = 0; k < nimg; k++) {
      check( pdata[k] = cpl_image_get_data_float(cpl_imagelist_get (iml, k)));
      check( pbinary[k] = cpl_mask_get_data(cpl_image_get_bpm(
                                               cpl_imagelist_get(iml, k))));
   }

   result=cpl_image_new(sx,sy,CPL_TYPE_FLOAT);
   pima=cpl_image_get_data_float(result);


   values=cpl_array_new(nimg,CPL_TYPE_FLOAT);


  for (i = 0; i < sx_sy; i++){


     for (count=0, k = 0; k < nimg; k++) {
        if ( ( (pbinary[k])[i] == CPL_BINARY_0) ) {
           cpl_array_set_float(values,k,(pdata[k])[i]);
           count++;
        } else {
           cpl_array_set_invalid(values,k);
        }

     }

     if(count>0) {
       pima[i]=cpl_array_get_median(values);
     } else {
        pima[i]=(pdata[0])[i];
     }

  }


  cleanup:

  cpl_array_delete(values);
  cpl_free(pdata);
  cpl_free(pbinary);

  return result;

}
