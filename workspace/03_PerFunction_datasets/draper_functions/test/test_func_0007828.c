xsh_image_mult_by_fct(const cpl_image* ima_dat,const int fctx,const int fcty)
{

  int nx=0;
  int ny=0;

  cpl_image* ima_datr=NULL;

  const float* pdat=NULL;
  float* pdatr=NULL;

  int i=0;
  int j=0;
  int k=0;
  int m=0;

  check(nx=cpl_image_get_size_x(ima_dat));
  check(ny=cpl_image_get_size_y(ima_dat));

  xsh_msg("org image size dat: %d %d",nx,ny);
  check(ima_datr=cpl_image_new(fctx*nx,fcty*ny,CPL_TYPE_FLOAT));
  xsh_msg("new image size dat: %d %d",fctx*nx,fcty*ny);

  check(pdat=cpl_image_get_data_float_const(ima_dat));
  check(pdatr=cpl_image_get_data_float(ima_datr));

  for(j=0;j<ny;j++) {
    for(m=0;m<fcty;m++) {
      for(i=0;i<nx;i++) {
	for(k=0;k<fctx;k++) {


	  pdatr[i*fctx+k+(j*fcty+m)*fctx*nx]=pdat[i+j*nx];
	}
      }
    }
  }

 cleanup:
  return ima_datr;
}
