xsh_ksigma_clip(const cpl_image * img,
		   int               llx,
		   int               lly,
		   int               urx,
		   int               ury,
		   double            kappa,
		   int               nclip,
		   double            tolerance,
		   double          * kmean,
		   double          * kstdev)
{

    int nx, ny;

    double      mean, stdev;
    int         npixs;
    cpl_image* sub_ima=NULL;
    double kappa2=0;
    double thresh=0;
    double thresh_p=0;
    cpl_binary * pm=0;
    const float* pi=0;

    int pix=0;
    int i=0;
    int j=0;
    int k=0;

    cpl_ensure_code(img != NULL, CPL_ERROR_NULL_INPUT);

    nx = cpl_image_get_size_x(img);
    ny = cpl_image_get_size_y(img);


    cpl_ensure_code(llx > 0 && urx > llx && urx <= nx &&
		    lly > 0 && ury > lly && ury <= ny,
		    CPL_ERROR_ILLEGAL_INPUT);

    cpl_ensure_code(tolerance >= 0.0, CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(kappa     >  1.0, CPL_ERROR_ILLEGAL_INPUT);
    cpl_ensure_code(nclip     >    0, CPL_ERROR_ILLEGAL_INPUT);

    sub_ima=cpl_image_extract(img,llx, lly, urx, ury);
   npixs= nx*ny-cpl_image_count_rejected(sub_ima);
   cpl_image_delete(sub_ima);
   mean    = cpl_image_get_mean_window(img,llx, lly, urx, ury);
   stdev    = cpl_image_get_stdev_window(img,llx, lly, urx, ury);
   pi=cpl_image_get_data_float_const(img);
   pm=cpl_mask_get_data(cpl_image_get_bpm((cpl_image*)img));


   kappa2=kappa*kappa;
   thresh_p=-1;
   for(k=0;k<nclip;k++) {
     mean    = cpl_image_get_mean_window(img,llx, lly, urx, ury);
     stdev    = cpl_image_get_stdev_window(img,llx, lly, urx, ury);
     thresh=stdev*stdev*kappa2;
     for(j=lly;j<ury;j++) {
       for(i=llx;i<urx;i++) {
	 pix=i+j*nx;
	 if(
             (pm[pix] != CPL_BINARY_1) &&
	     ((pi[pix]-mean)*(pi[pix]-mean) > thresh ) ) {
	   pm[pix]=CPL_BINARY_1;
	 }
       }
     }
     if((fabs(thresh_p-thresh)) < tolerance) {
       break;
     } else {
       thresh_p=thresh;
     }
   }

    *kmean = mean;
    if (kstdev != NULL) *kstdev = stdev;


    return cpl_error_get_code();
}
