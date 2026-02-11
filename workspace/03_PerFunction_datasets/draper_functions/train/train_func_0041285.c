s_table_new(int rows, int cols)
{
  TABLE **new_table;
  int i, j;


  new_table = (TABLE **) g_malloc(rows*sizeof(TABLE *));
  for (i = 0; i < rows; i++) {
    new_table[i] = (TABLE *) g_malloc(cols * sizeof(TABLE));


  }


  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      (new_table[i][j]).attrib_value = NULL;
      (new_table[i][j]).row_name = NULL;
      (new_table[i][j]).col_name = NULL;
      (new_table[i][j]).row = i;
      (new_table[i][j]).col = j;
      (new_table[i][j]).visibility = VISIBLE;
      (new_table[i][j]).show_name_value = SHOW_VALUE;
    }
  }

  return (new_table);

}
