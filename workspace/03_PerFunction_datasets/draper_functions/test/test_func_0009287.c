city_report_dialog_store_new(void)
{
  GType model_types[NUM_CREPORT_COLS + 1];
  gint i;


  for (i = 0; i < NUM_CREPORT_COLS; i++) {
    model_types[i] = G_TYPE_STRING;
  }


  model_types[i++] = G_TYPE_INT;

  return gtk_list_store_newv(i, model_types);
}
