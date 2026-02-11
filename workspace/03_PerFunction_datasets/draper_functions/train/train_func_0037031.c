calc_weights(AmitkDataSet * ds) {

  gdouble * weight;
  gint num_frames, t;
  gdouble total_weight;

  num_frames = AMITK_DATA_SET_NUM_FRAMES(ds);

  weight = g_try_new(gdouble, num_frames);
  g_return_val_if_fail(weight != NULL, NULL);


  total_weight = 0;
  for (t=0; t<num_frames; t++) {
    weight[t] = amitk_data_set_get_frame_duration(ds, t);
    total_weight += weight[t];
  }
  for (t=0; t<num_frames; t++)
    weight[t] *= (num_frames/total_weight);

  return weight;
}
