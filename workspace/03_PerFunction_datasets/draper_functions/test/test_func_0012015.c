sinfo_convolve_kernel(cpl_table** t, const int rad)
{
  int i=0;
  int j=0;
  int np=0;
  double val=0;
  double* pidata=NULL;
  double* pcdata=NULL;
  double dw=0;

  double ws=0;
  double we=0;
  cknull(*t,"null input table");
  check_nomsg(cpl_table_new_column(*t,"CNV",CPL_TYPE_DOUBLE));
  check_nomsg(pidata=cpl_table_get_data_double(*t,"INT"));
  check_nomsg(pcdata=cpl_table_get_data_double(*t,"CNV"));
  check_nomsg(ws=cpl_table_get_column_min(*t,"WAVE"));
  check_nomsg(we=cpl_table_get_column_max(*t,"WAVE"));
  check_nomsg(np=cpl_table_get_nrow(*t));
  dw=(we-ws)/(np-1);


  for(i=0;i<rad;i++) {
    pcdata[i]=0.;
  }
  for(i=np-rad;i<np;i++) {
    pcdata[i]=0.;
  }
  for(i=rad;i<np-rad;i++) {
    val=0;
    for(j=-rad;j<rad;j++) {
      val+=pidata[i+j];
    }

    check_nomsg(cpl_table_set_double(*t,"CNV",i,val));
  }
  return 0;

 cleanup:
  return -1;

}
