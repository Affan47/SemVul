sinfo_scales_obj_sky_cubes(cpl_imagelist* obj_cub,
                            cpl_imagelist* sky_cub,
                            cpl_table* bkg,
                            cpl_table* rscale,
                            cpl_imagelist** obj_cor)
{


  int i=0;
  int j=0;
  int k=0;
  int xsz=0;
  int ysz=0;
  int zsz=0;

  double* podata=NULL;
  double* psdata=NULL;
  double* pbdata=NULL;
  double* pcdata=NULL;
  double* pscale=NULL;


  cpl_image* imgo=NULL;
  cpl_image* imgs=NULL;
  cpl_image* imgc=NULL;


  check_nomsg(imgo=cpl_imagelist_get(obj_cub,0));
  check_nomsg(xsz=cpl_image_get_size_x(imgo));
  check_nomsg(ysz=cpl_image_get_size_y(imgo));
  check_nomsg(zsz=cpl_imagelist_get_size(obj_cub));

  check_nomsg(*obj_cor=cpl_imagelist_duplicate(obj_cub));

  for(k=0;k<zsz;k++) {
    check_nomsg(imgo=cpl_imagelist_get(obj_cub,k));
    check_nomsg(imgc=cpl_imagelist_get(*obj_cor,k));
    check_nomsg(imgs=cpl_imagelist_get(sky_cub,k));

    check_nomsg(podata=cpl_image_get_data_double(imgo));
    check_nomsg(pcdata=cpl_image_get_data_double(imgc));
    check_nomsg(psdata=cpl_image_get_data_double(imgs));
    check_nomsg(pbdata=cpl_table_get_data_double(bkg,"INT2"));
    check_nomsg(pscale=cpl_table_get_data_double(rscale,"RATIO"));

    for (j=0;j<ysz; j++) {
      for (i=0;i<xsz; i++) {
        if(!irplib_isnan(podata[i+j*xsz]) &&
           !irplib_isnan(psdata[i+j*xsz]) &&
           !irplib_isnan(pbdata[k]) &&
           !irplib_isnan(pscale[k])) {
    pcdata[i+j*xsz] = podata[i+j*xsz]-
                          (psdata[i+j*xsz]-pbdata[k])*pscale[k];
    }
      }
    }
  }


  return 0;
 cleanup:

  return -1;
}
