sinfo_table_extract_finite(const cpl_table* in1,
                           const cpl_table* in2,
                                 cpl_table** ou1,
                                 cpl_table** ou2)
{

  int size1=0;
  int size2=0;
  int i=0;
  int ninv1=0;
  int ninv2=0;
  double* pout1=NULL;
  double* pout2=NULL;

  cknull(in1,"null input image");
  cknull(in2,"null input image");
  cknull_nomsg(*ou1=cpl_table_duplicate(in1));
  cknull_nomsg(*ou2=cpl_table_duplicate(in2));

  check_nomsg(size1=cpl_table_get_nrow(*ou1));
  check_nomsg(size2=cpl_table_get_nrow(*ou2));

  check_nomsg(pout1=cpl_table_get_data_double(*ou1,"VALUE"));
  check_nomsg(pout2=cpl_table_get_data_double(*ou2,"VALUE"));
  for(i=0;i<size1;i++) {
    if (irplib_isnan(pout1[i])) {
      check_nomsg(cpl_table_set_invalid(*ou1,"VALUE",i));
      check_nomsg(cpl_table_set_invalid(*ou2,"VALUE",i));
    }
  }
  ninv1=cpl_table_count_invalid(*ou1,"VALUE");
  ninv2=cpl_table_count_invalid(*ou2,"VALUE");
  if(ninv1==size1) {
    goto cleanup;
  }
  if(ninv2==size2) {
    goto cleanup;
  }
  check_nomsg(cpl_table_erase_invalid(*ou1));
  check_nomsg(cpl_table_erase_invalid(*ou2));
  return (size1-ninv1);

 cleanup:
  return 0;

}
