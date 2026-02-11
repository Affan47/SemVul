_frogr_photoset_set_property (GObject *object,
                              guint prop_id,
                              const GValue *value,
                              GParamSpec *pspec)
{
  FrogrPhotoSet *self = FROGR_PHOTOSET (object);

  switch (prop_id)
    {
    case PROP_TITLE:
      frogr_photoset_set_title (self, g_value_get_string (value));
      break;
    case PROP_DESCRIPTION:
      frogr_photoset_set_description (self, g_value_get_string (value));
      break;
    case PROP_ID:
      frogr_photoset_set_id (self, g_value_get_string (value));
      break;
    case PROP_LOCAL_ID:
      frogr_photoset_set_local_id (self, g_value_get_string (value));
      break;
    case PROP_PRIMARY_PHOTO_ID:
      frogr_photoset_set_primary_photo_id (self, g_value_get_string (value));
      break;
    case PROP_N_PHOTOS:
      frogr_photoset_set_n_photos (self, g_value_get_int (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
