ges_track_element_create_gnl_object_func (GESTrackElement * self)
{
  GESTrackElementClass *klass = NULL;
  GstElement *child = NULL;
  GstElement *gnlobject;

  klass = GES_TRACK_ELEMENT_GET_CLASS (self);

  if (G_UNLIKELY (self->priv->gnlobject != NULL))
    goto already_have_gnlobject;

  if (G_UNLIKELY (klass->gnlobject_factorytype == NULL))
    goto no_gnlfactory;

  GST_DEBUG ("Creating a supporting gnlobject of type '%s'",
      klass->gnlobject_factorytype);

  gnlobject = gst_element_factory_make (klass->gnlobject_factorytype, NULL);

  if (G_UNLIKELY (gnlobject == NULL))
    goto no_gnlobject;

  if (klass->create_element) {
    GST_DEBUG ("Calling subclass 'create_element' vmethod");
    child = klass->create_element (self);

    if (G_UNLIKELY (!child))
      goto child_failure;

    if (!gst_bin_add (GST_BIN (gnlobject), child))
      goto add_failure;

    GST_DEBUG ("Succesfully got the element to put in the gnlobject");
    self->priv->element = child;
  }

  GST_DEBUG ("done");
  return gnlobject;


already_have_gnlobject:
  {
    GST_ERROR ("Already controlling a GnlObject %s",
        GST_ELEMENT_NAME (self->priv->gnlobject));
    return NULL;
  }

no_gnlfactory:
  {
    GST_ERROR ("No GESTrackElement::gnlobject_factorytype implementation!");
    return NULL;
  }

no_gnlobject:
  {
    GST_ERROR ("Error creating a gnlobject of type '%s'",
        klass->gnlobject_factorytype);
    return NULL;
  }

child_failure:
  {
    GST_ERROR ("create_element returned NULL");
    gst_object_unref (gnlobject);
    return NULL;
  }

add_failure:
  {
    GST_ERROR ("Error adding the contents to the gnlobject");
    gst_object_unref (child);
    gst_object_unref (gnlobject);
    return NULL;
  }
}
