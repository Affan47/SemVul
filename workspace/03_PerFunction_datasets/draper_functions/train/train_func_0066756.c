frogr_model_serialize (FrogrModel *self)
{
  JsonArray *json_array = NULL;
  JsonObject *root_object = NULL;
  GSList *data_list = NULL;

  g_return_val_if_fail(FROGR_IS_MODEL (self), NULL);

  root_object = json_object_new ();

  data_list = frogr_model_get_pictures (self);
  json_array = _serialize_list_to_json_array (data_list, G_TYPE_OBJECT);
  json_object_set_array_member (root_object, "pictures", json_array);

  data_list = frogr_model_get_photosets (self);
  json_array = _serialize_list_to_json_array (data_list, G_TYPE_OBJECT);
  json_object_set_array_member (root_object, "photosets", json_array);

  data_list = frogr_model_get_groups (self);
  json_array = _serialize_list_to_json_array (data_list, G_TYPE_OBJECT);
  json_object_set_array_member (root_object, "groups", json_array);


  json_array = _serialize_list_to_json_array (FROGR_MODEL_GET_PRIVATE (self)->local_tags,
                                              G_TYPE_STRING);
  json_object_set_array_member (root_object, "tags", json_array);

  return root_object;
}
