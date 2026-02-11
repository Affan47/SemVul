sort_datasets_by_dicom_params(gconstpointer a, gconstpointer b) {

  g_return_val_if_fail(a != NULL, 0);
  g_return_val_if_fail(b != NULL, 0);


  if (AMITK_DATA_SET_SERIES_NUMBER(a) > AMITK_DATA_SET_SERIES_NUMBER(b))
    return 1;
  else if (AMITK_DATA_SET_SERIES_NUMBER(a) < AMITK_DATA_SET_SERIES_NUMBER(b))
    return -1;


  if (!isnan(AMITK_DATA_SET_ECHO_TIME(a)) && !isnan(AMITK_DATA_SET_ECHO_TIME(b))) {
    if (AMITK_DATA_SET_ECHO_TIME(a) > AMITK_DATA_SET_ECHO_TIME(b))
      return 1;
    else if (AMITK_DATA_SET_ECHO_TIME(a) < AMITK_DATA_SET_ECHO_TIME(b))
      return -1;
  }

  return 0;
}
