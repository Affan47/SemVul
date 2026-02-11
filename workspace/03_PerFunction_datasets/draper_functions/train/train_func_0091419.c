amitk_data_set_set_conversion(AmitkDataSet * ds, AmitkConversion new_conversion) {

  g_return_if_fail(AMITK_IS_DATA_SET(ds));

  if (ds->conversion != new_conversion) {
    ds->conversion = new_conversion;
    amitk_data_set_set_scale_factor(ds, calculate_scale_factor(ds));
    g_signal_emit(G_OBJECT (ds), data_set_signals[CONVERSION_CHANGED], 0);
  }
}
