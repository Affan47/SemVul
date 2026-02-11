html_table_begin(Html_table *tab, Dsvec *attrs, int max_cols)
{
  int i;

  tab->curr_col = 0;
  tab->curr_row = 0;
  tab->in_row = 0;
  tab->in_header = 0;
  if (max_cols)
	tab->max_cols = max_cols;

  ds_asprintf(tab->ds, "<table");
  for (i = 0; i < dsvec_len(attrs); i++) {
	char *p;

	p = (char *) dsvec_ptr_index(attrs, i);
	ds_asprintf(tab->ds, " %s", p);
  }
  ds_asprintf(tab->ds, ">\n");

  return(0);
}
