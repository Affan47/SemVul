visu_ui_color_combobox_setRangeMaterial(VisuUiColorCombobox *colorComboBox, float material[5],
			       gboolean raiseSignal)
{
  int i;

  g_return_if_fail(VISU_UI_IS_COLOR_COMBOBOX(colorComboBox));
  g_return_if_fail(colorComboBox->withRanges);

  if (raiseSignal)
    for (i = 0; i < VISU_GL_LIGHT_MATERIAL_N_VALUES; i++)
      gtk_range_set_value(GTK_RANGE(colorComboBox->materialRanges[i]),
			  (gdouble)material[i]);
  else
    for (i = 0; i < VISU_GL_LIGHT_MATERIAL_N_VALUES; i++)
      {
	g_signal_handler_block(G_OBJECT(colorComboBox->materialRanges[i]),
			       colorComboBox->materialSignals[i]);
	gtk_range_set_value(GTK_RANGE(colorComboBox->materialRanges[i]),
			    (gdouble)material[i]);
	g_signal_handler_unblock(G_OBJECT(colorComboBox->materialRanges[i]),
				 colorComboBox->materialSignals[i]);
      }
}
