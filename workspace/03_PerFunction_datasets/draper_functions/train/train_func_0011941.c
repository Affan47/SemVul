sinfo_table_threshold(cpl_table** t,
                      const char* column,
                      const double low_cut,
                      const double hig_cut,
                      const double low_ass,
                      const double hig_ass)
{

  int nrow=0;
  int i=0;
  double* pdata=NULL;
  cknull(*t,"null input table!");

  check_nomsg(nrow=cpl_table_get_nrow(*t));
  check_nomsg(pdata=cpl_table_get_data_double(*t,column));

  for(i=0;i<nrow;i++) {

    if(pdata[i]<low_cut) {
      pdata[i]=low_ass;
    }
    if (pdata[i] >= hig_cut) {
      pdata[i]=hig_ass;
    }

  }

  return 0;

 cleanup:

  return -1;
}
