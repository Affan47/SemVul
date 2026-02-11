real_city_dialog_popup(struct city *pcity)
{
  struct city_dialog *pdialog;

  if (!(pdialog = get_city_dialog(pcity))) {
    pdialog = create_city_dialog(pcity);
  }

  gtk_window_present(GTK_WINDOW(pdialog->shell));


  city_dialog_map_recenter(pdialog->overview.map_canvas.sw);
  if (pdialog->happiness.map_canvas.sw) {
    city_dialog_map_recenter(pdialog->happiness.map_canvas.sw);
  }
}
