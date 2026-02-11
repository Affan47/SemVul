useDataFileColor(GtkToggleButton *toggle, gpointer data _U_)
{
  gboolean isOn;
  int res;
  VisuData *dataObj;

  dataObj = visu_ui_panel_getData(VISU_UI_PANEL(panelDataFile));
  if (!dataObj)
    return;

  isOn = gtk_toggle_button_get_active(toggle);
  res = visu_colorization_setUsed(dataObj, (gboolean)isOn);
  makeColorPreview(dataObj);


  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkHideMinValues)))
    applyHideMinValues(dataObj, FALSE);
  if (res)
    {
      g_signal_emit_by_name(G_OBJECT(dataObj), "RenderingChanged", (VisuElement*)0, NULL);
      VISU_REDRAW_ADD;
    }
}
