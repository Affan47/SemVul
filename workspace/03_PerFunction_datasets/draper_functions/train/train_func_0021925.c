static_show (gamgi_window *window)
{
GtkWidget *dialog = window->dialog1;
GtkWidget *treeview;
GtkListStore *store;
char *indices;
int *range;
int i, j, k;
int ii, jj, kk;
int b, c;

indices = list.indices;
range = list.range;


store = gtk_list_store_new (1, G_TYPE_STRING);

if (indices != NULL)
  {
  b = range[3] - range[2] + 1;
  c = range[5] - range[4] + 1;

  for (i = range[1]; i >= range[0]; i--)
    {
    ii = i - range[0];
    for (j = range[3]; j >= range[2]; j--)
      {
      jj = j - range[2];
      for (k = range[5]; k >= range[4]; k--)
        {
        kk = k - range[4];

        if (i == 0 && j == 0 && k == 0) continue;
        if (indices[b * c * ii + c * jj + kk] == TRUE)
          static_row (store, i, j, k);
        }
      }
    }
  }

treeview = (GtkWidget *) g_object_get_data (G_OBJECT (dialog), "treeview");
gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), GTK_TREE_MODEL (store));
g_object_unref (store);
}
