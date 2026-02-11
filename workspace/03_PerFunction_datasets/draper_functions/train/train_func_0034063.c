add_ggobi_sheets(ggobid *gg, GtkWidget *notebook)
{
  GGobiData *data;
  GSList *el;

  el = gg->d;
  while(el) {
   GtkWidget *label;
   GtkWidget *sheet;
   data = (GGobiData*) el->data;

   if (g_slist_length (data->vartable)) {
     label = gtk_label_new(data->name);
     sheet = create_ggobi_sheet(data, gg);
     gtk_notebook_append_page(GTK_NOTEBOOK(notebook), GTK_WIDGET(sheet), label);
   }

   el = el->next;
  }
}
