sinfo_fit_sky(double p[])

{
  double* ps=NULL;
  double* po=NULL;
  double* pv=NULL;
  cpl_vector* vtmp=NULL;
  int i=0;
  int np=0;
  cpl_size pows[2];
  double mse=0;
  double cont=0;
  cpl_polynomial* pfit=NULL;

  double rms=0;


  check_nomsg(pfit=sinfo_polynomial_fit_1d_create(sa_ox,sa_oy,0,&mse));
  pows[0]=0;
  pows[1]=0;
  check_nomsg(cont=cpl_polynomial_get_coeff(pfit,pows));
  check_nomsg(sinfo_free_polynomial(&pfit));
  check_nomsg(cpl_vector_subtract_scalar(sa_oy,cont));


  check_nomsg(pfit=sinfo_polynomial_fit_1d_create(sa_ox,sa_sy,0,&mse));
  pows[0]=0;
  pows[1]=0;
  check_nomsg(cont=cpl_polynomial_get_coeff(pfit,pows));
  check_nomsg(sinfo_free_polynomial(&pfit));
  check_nomsg(cpl_vector_subtract_scalar(sa_sy,cont));


  check_nomsg(po= cpl_vector_get_data(sa_oy));
  check_nomsg(ps= cpl_vector_get_data(sa_sy));

  check_nomsg(np=cpl_vector_get_size(sa_oy));
  check_nomsg(vtmp=cpl_vector_new(np));
  check_nomsg(pv= cpl_vector_get_data(vtmp));


  for(i=0;i<np;i++) {
    pv[i]=po[i]-ps[i]*p[0];
  }

  check_nomsg(rms=cpl_vector_get_stdev(vtmp));
  sinfo_free_my_vector(&vtmp);
  return rms;
 cleanup:
  sinfo_free_my_vector(&vtmp);
  return -1;

}
