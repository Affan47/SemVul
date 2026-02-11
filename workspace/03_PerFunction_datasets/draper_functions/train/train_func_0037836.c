xsh_grid2table( xsh_grid* grid)
{
  int i = 0;
  cpl_table* tab=NULL;
  double* px=NULL;
  double* py=NULL;
  double* pi=NULL;
  double* pe=NULL;


  int nrows=0;


  XSH_ASSURE_NOT_NULL(grid);


  nrows= grid->idx;
  tab=cpl_table_new(nrows);
  cpl_table_new_column(tab,"X",CPL_TYPE_DOUBLE);
  cpl_table_new_column(tab,"Y",CPL_TYPE_DOUBLE);
  cpl_table_new_column(tab,"INT",CPL_TYPE_DOUBLE);
  cpl_table_new_column(tab,"ERR",CPL_TYPE_DOUBLE);

  cpl_table_fill_column_window(tab,"X",0,nrows,-1);
  cpl_table_fill_column_window(tab,"Y",0,nrows,-1);
  cpl_table_fill_column_window(tab,"INT",0,nrows,-1);
  cpl_table_fill_column_window(tab,"ERR",0,nrows,-1);

  px=cpl_table_get_data_double(tab,"X");
  py=cpl_table_get_data_double(tab,"Y");
  pi=cpl_table_get_data_double(tab,"INT");
  pe=cpl_table_get_data_double(tab,"ERR");

  for (i = 0; i < nrows; i++) {
    px[i] = grid->list[i]->x;
    py[i] = grid->list[i]->y;
    pi[i] = grid->list[i]->v;
    pe[i] = grid->list[i]->errs;
  }

  cleanup:
    return tab;
}
