add_ggobi_data(GGobiData *data, GtkTreeModel *model)
{
  gint i, j, k, level;
  gboolean level_ok;
  const gfloat **raw;
  vartabled *vt;

  gchar *str;

  raw = GGOBI(getRawData)(data, data->gg);
  for(i = 0; i < data->nrows; i++) {
    GtkTreeIter iter;
	gtk_list_store_append(GTK_LIST_STORE(model), &iter);

	str = (gchar *) g_array_index(data->rowlab, gchar*, i);
	gtk_list_store_set(GTK_LIST_STORE(model), &iter, 0, str, -1);

  for(j = 0; j < data->ncols; j++) {
    vt = g_slist_nth_data(data->vartable, j);

    if(ggobi_data_is_missing(data, i, j) && vt->vartype != categorical);

	  else {
      if(vt->vartype == categorical)  {
        gchar *level_str;
        level_ok = false;
        for (k=0; k<vt->nlevels; k++) {
          if ((gint)raw[i][j] == vt->level_values[k]) {
            level = k;
            level_ok = true;
            break;
          }
        }
        if (level_ok)
          level_str = vt->level_names[level];
        else level_str = "<improper level>";
          gtk_list_store_set(GTK_LIST_STORE(model), &iter, j+1, level_str, -1);
       } else {
         gtk_list_store_set(GTK_LIST_STORE(model), &iter, j+1, raw[i][j], -1);
       }
      }
    }
  }
}
