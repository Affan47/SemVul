ds_conversion_changed_cb(AmitkDataSet * ds, AmitkThreshold * threshold) {

  g_return_if_fail(AMITK_IS_DATA_SET(ds));
  g_return_if_fail(AMITK_IS_THRESHOLD(threshold));

  threshold_update_spin_buttons(threshold);
  threshold_update_absolute_label(threshold);

  return;
}
