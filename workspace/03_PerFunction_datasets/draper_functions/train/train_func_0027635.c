visu_ui_panel_colorization_setRangeMode(VisuColorizationInputScaleId mode)
{

  if (!panelDataFileIsInitiated)
    {
      panelDataFileIsInitiated = TRUE;
      createInteriorDataFile();
    }

  if (mode == VISU_COLORIZATION_NORMALIZE)
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioNormalized), TRUE);
  else
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radioMinMax), TRUE);
}
