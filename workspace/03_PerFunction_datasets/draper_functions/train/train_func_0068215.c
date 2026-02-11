sinfo_table_shift_simple(cpl_table* inp,
                         const char* col,
                         const double shift)
{

  int nrow=0;
  cpl_table* out=NULL;
  int is=(int)shift;
  double ds=shift-is;
  double* pi=NULL;
  double* po=NULL;
  double m=0;
  int i=0;
  cknull(inp,"null input table");

  check_nomsg(nrow=cpl_table_get_nrow(inp));
  check_nomsg(out=cpl_table_duplicate(inp));
  check_nomsg(cpl_table_fill_column_window(out,col,0,nrow,0));
  check_nomsg(pi=cpl_table_get_data_double(inp,col));
  check_nomsg(po=cpl_table_get_data_double(out,col));


  for(i=0;i<nrow;i++) {
    if((i+is)>0 && (i+is+1) < nrow) {
      m=pi[i+is+1]-pi[i+is];
      po[i]=pi[i+is]+m*ds;
    }
  }
  return out;
  cleanup:
  sinfo_free_table(&out);
  return NULL;

}
