gst_play_base_bin_get_streaminfo_value_array (GstPlayBaseBin * play_base_bin)
{
  GstPlayBaseGroup *group;
  GValueArray *array = NULL;

  GROUP_LOCK (play_base_bin);
  group = get_active_group (play_base_bin);
  if (group) {
    array = g_value_array_copy (group->streaminfo_value_array);
  } else {
    array = g_value_array_new (0);
  }
  GROUP_UNLOCK (play_base_bin);

  return array;
}
