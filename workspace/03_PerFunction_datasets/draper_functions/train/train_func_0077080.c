_perform_after_upload_operations (FrogrController *controller, UploadOnePictureData *uop_data)
{
  if (frogr_picture_get_license (uop_data->picture) != FSP_LICENSE_NONE)
    {
      uop_data->after_upload_attempts[AFTER_UPLOAD_OP_SETTING_LICENSE] = 0;
      _set_license_for_picture (controller, uop_data);
    }

  if (frogr_picture_send_location (uop_data->picture)
      && frogr_picture_get_location (uop_data->picture) != NULL)
    {
      uop_data->after_upload_attempts[AFTER_UPLOAD_OP_SETTING_LOCATION] = 0;
      _set_location_for_picture (controller, uop_data);
    }

  if (frogr_picture_get_photosets (uop_data->picture))
    {
      uop_data->photosets = frogr_picture_get_photosets (uop_data->picture);
      _add_picture_to_photosets_or_create (controller, uop_data);
    }

  if (frogr_picture_get_groups (uop_data->picture))
    {
      uop_data->groups = frogr_picture_get_groups (uop_data->picture);
      _add_picture_to_groups (controller, uop_data);
    }
}
