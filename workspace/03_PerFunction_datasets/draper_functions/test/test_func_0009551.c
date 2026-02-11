gst_scene_change_finalize (GObject * object)
{
  GstSceneChange *scenechange;

  g_return_if_fail (GST_IS_SCENE_CHANGE (object));
  scenechange = GST_SCENE_CHANGE (object);

  if (scenechange->oldbuf)
    gst_buffer_unref (scenechange->oldbuf);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
