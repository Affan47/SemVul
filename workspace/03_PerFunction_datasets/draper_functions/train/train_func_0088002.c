xsh_mflat_normalize(xsh_order_list * order_table, xsh_pre* pre_mflat)
{

  float* pflux=NULL;
  float* psmo=NULL;
  int* pqual=NULL;
  int iorder=0;
  int abs_order=0;
  float flux_max=FLT_MIN;
  int minx=0;
  int miny=0;
  int maxx=0;
  int maxy=0;
  int sx=0;
  int sy=0;


  int iy=0;
  int ix=0;
  int rad=2;
  float flux=0;
  cpl_image* data=NULL;
  cpl_image* smo=NULL;

  XSH_ASSURE_NOT_NULL( order_table);
  XSH_ASSURE_NOT_NULL( pre_mflat);
  data=xsh_pre_get_data(pre_mflat);

  smo=xsh_image_smooth_median_x(data,rad);

  check( pflux = cpl_image_get_data_float( data));
  check( psmo = cpl_image_get_data_float( smo));
  check( pqual = cpl_image_get_data_int  ( xsh_pre_get_qual( pre_mflat )));

  sx = xsh_pre_get_nx( pre_mflat);
  sy = xsh_pre_get_ny( pre_mflat);

  for ( iorder = 0; iorder < order_table->size; iorder++){
    miny = xsh_order_list_get_starty( order_table, iorder);
    maxy = xsh_order_list_get_endy( order_table, iorder);
    abs_order = order_table->list[iorder].absorder ;

    for( iy = miny ; iy < maxy ; iy++ ) {
      check( minx = xsh_order_list_eval_int(order_table,
					    order_table->list[iorder].edglopoly, iy)-3);
      check( maxx = xsh_order_list_eval_int(order_table,
					    order_table->list[iorder].edguppoly, iy)+2);


      flux_max=FLT_MIN;
      for( ix = minx ; ix <= maxx; ix++){
        if(pqual[iy*sx+ix]==0) {
          flux=psmo[iy*sx+ix];
	  flux_max = (flux>flux_max)? flux : flux_max;
	}
      }

      for( ix = minx ; ix <= maxx; ix++){
        pflux[iy*sx+ix]/=flux_max;
      }
    }
  }

 cleanup:
   xsh_free_image(&smo);
   return cpl_error_get_code();

}
