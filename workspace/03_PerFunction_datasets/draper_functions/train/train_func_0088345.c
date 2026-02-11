static_reset (GtkWidget* vbox, int page)
{
GtkWidget *entry;


entry = (GtkWidget *) g_object_get_data (G_OBJECT (vbox), "entry_object0");
gtk_entry_set_text (GTK_ENTRY (entry), "");
switch (page)
  {
  case 0: case 1:
  entry = (GtkWidget *) g_object_get_data (G_OBJECT (vbox), "entry_object1");
  gtk_entry_set_text (GTK_ENTRY (entry), "");
  entry = (GtkWidget *) g_object_get_data (G_OBJECT (vbox), "entry_object2");
  gtk_entry_set_text (GTK_ENTRY (entry), "");
  entry = (GtkWidget *) g_object_get_data (G_OBJECT (vbox), "entry_object3");
  gtk_entry_set_text (GTK_ENTRY (entry), "");
  break;
  }
entry = g_object_get_data (G_OBJECT (vbox), "entry_value");
gtk_entry_set_text (GTK_ENTRY (entry), "");
}
