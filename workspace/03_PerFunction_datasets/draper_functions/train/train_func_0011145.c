gst_object_dispose (GObject * object)
{
  GstObject *self = (GstObject *) object;
  GstObject *parent;

  GST_CAT_TRACE_OBJECT (GST_CAT_REFCOUNTING, object, "dispose");

  GST_OBJECT_LOCK (object);
  if ((parent = GST_OBJECT_PARENT (object)))
    goto have_parent;
  GST_OBJECT_PARENT (object) = NULL;
  GST_OBJECT_UNLOCK (object);

  if (self->control_bindings) {
    GList *node;

    for (node = self->control_bindings; node; node = g_list_next (node)) {
      gst_object_unparent (node->data);
    }
    g_list_free (self->control_bindings);
    self->control_bindings = NULL;
  }

  ((GObjectClass *) gst_object_parent_class)->dispose (object);

  return;


have_parent:
  {
    g_critical ("\nTrying to dispose object \"%s\", but it still has a "
        "parent \"%s\".\nYou need to let the parent manage the "
        "object instead of unreffing the object directly.\n",
        GST_OBJECT_NAME (object), GST_OBJECT_NAME (parent));
    GST_OBJECT_UNLOCK (object);

    gst_object_ref (object);
    return;
  }
}
