html_cell_format(Html_table *tab, char *content, Html_cell *cell)
{
  Html_table xtab;

  if (!tab->in_row)
	return(0);

  xtab = *tab;
  xtab.ds = NULL;

  if (tab->max_cols && tab->curr_col == tab->max_cols)
	html_row_begin(&xtab);

  cell->id = NULL;
  cell->row = xtab.curr_row;
  cell->column = xtab.curr_col;
  cell->attrs = NULL;

  if (tab->cell_desc != NULL) {
	Html_cell *desc;

	desc = (Html_cell *) dsvec_ptr_index(tab->cell_desc, tab->curr_col);
	cell->class = desc->class;
	cell->width = desc->width;
	cell->align = desc->align;
	cell->valign = desc->valign;
  }
  else {
	cell->class = NULL;
	cell->width = 0;
	cell->align = NULL;
	cell->valign = NULL;
  }

  if (cell->class == NULL && tab->auto_column_class != NULL)
	cell->class = ds_xprintf("%s_%d", tab->auto_column_class, cell->column + 1);

  if (content == NULL) {
	if (tab->default_cell_contents == NULL)
	  cell->content = "&nbsp;";
	else
	  cell->content = tab->default_cell_contents;
  }
  else
	cell->content = content;

  return(1);
}
