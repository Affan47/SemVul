gnlobject_priority_cb (GstElement * gnlobject, GParamSpec * arg G_GNUC_UNUSED,
    GESTrackObject * obj)
{
  guint32 priority;
  GESTrackObjectClass *klass;

  klass = GES_TRACK_OBJECT_GET_CLASS (obj);

  g_object_get (gnlobject, "priority", &priority, NULL);

  GST_DEBUG ("gnlobject priority : %d current : %d", priority, obj->priority);

  if (priority != obj->priority) {
    obj->priority = priority;
    if (klass->gnl_priority_changed)
      klass->gnl_priority_changed (obj, priority);
  }
}
