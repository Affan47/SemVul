_fetch_everything (FrogrController *self, gboolean force_extra_data)
{
  g_return_if_fail(FROGR_IS_CONTROLLER (self));

  if (!frogr_controller_is_authorized (self))
    return;


  if (force_extra_data)
    _invalidate_extra_data (self);

  FetchAccountInfoData *data = g_slice_new0 (FetchAccountInfoData);
  data->retrieve_everything = TRUE;
  data->force_extra_data = force_extra_data;

  _fetch_account_basic_info (self, data);
}
