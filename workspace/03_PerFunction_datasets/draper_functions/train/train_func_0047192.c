gst_type_find_factory_call_function (GstTypeFindFactory * factory,
    GstTypeFind * find)
{
  GstTypeFindFactory *new_factory;

  g_return_if_fail (GST_IS_TYPE_FIND_FACTORY (factory));
  g_return_if_fail (find != NULL);
  g_return_if_fail (find->peek != NULL);
  g_return_if_fail (find->suggest != NULL);

  new_factory =
      GST_TYPE_FIND_FACTORY (gst_plugin_feature_load (GST_PLUGIN_FEATURE
          (factory)));
  if (new_factory) {
    if (new_factory->function)
      new_factory->function (find, new_factory->user_data);
    gst_object_unref (new_factory);
  }
}
