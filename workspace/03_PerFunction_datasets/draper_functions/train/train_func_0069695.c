object_pad_removed (GnlObject * object, GstPad * pad, GnlComposition * comp)
{
  GST_DEBUG_OBJECT (comp, "pad %s:%s was removed", GST_DEBUG_PAD_NAME (pad));


  if (GST_PAD_IS_SRC (pad) && comp->priv->current
      && ((GnlObject *) comp->priv->current->data == object)
      && comp->priv->ghostpad) {
    GST_DEBUG_OBJECT (comp, "Removing ghostpad");
    gnl_object_remove_ghost_pad ((GnlObject *) comp, comp->priv->ghostpad);
    comp->priv->ghostpad = NULL;
    comp->priv->ghosteventprobe = 0;
  } else {

    gst_pad_set_blocked_async (pad, FALSE, (GstPadBlockCallback) pad_blocked,
        comp);
  }
}
