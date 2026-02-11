photos_tracker_queue_data_free (PhotosTrackerQueueData *data)
{
  g_clear_object (&data->cancellable);
  g_free (data->sparql);

  if (data->destroy_data != NULL)
    (*data->destroy_data) (data->user_data);

  g_slice_free (PhotosTrackerQueueData, data);
}
