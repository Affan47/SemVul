load_column_labels (Row * row, GGobiData * d, gboolean row_labels)
{
  gint i;
  gint offset = (row_labels ? 1 : 0);
  for (i = 0; i < d->ncols; i++) {
    if (row->entry[i + offset].len == 0)
      ggobi_data_set_col_name(d, i, NULL);
    else
      ggobi_data_set_col_name(d, i, row->src->str + row->entry[i + offset].ofs);
  }
}
