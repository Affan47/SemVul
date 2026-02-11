free_candidate_signal_data (gpointer user_data)
{
  struct candidate_signal_data *data = user_data;
  fs_candidate_destroy (data->candidate1);
  if (data->candidate2)
    fs_candidate_destroy (data->candidate2);
  g_object_unref (data->self);
  g_slice_free (struct candidate_signal_data, data);
}
