threshold_update_absolute_label(AmitkThreshold * threshold) {

  guint i_ref;

  if (threshold->minimal) return;
  g_return_if_fail(AMITK_IS_DATA_SET(threshold->data_set));

  for (i_ref=0; i_ref<2; i_ref++) {

    switch (AMITK_DATA_SET_CONVERSION(threshold->data_set)) {
    case AMITK_CONVERSION_SUV:
    case AMITK_CONVERSION_PERCENT_ID_PER_CC:
      gtk_label_set_text(GTK_LABEL(threshold->absolute_label[i_ref]),
			 amitk_conversion_names[AMITK_DATA_SET_CONVERSION(threshold->data_set)]);
      break;
    case AMITK_CONVERSION_STRAIGHT:
    default:
      gtk_label_set_text(GTK_LABEL(threshold->absolute_label[i_ref]), _("Absolute"));
      break;
    }

  }

  return;
}
