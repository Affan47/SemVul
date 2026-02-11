ges_test_clip_set_mute (GESTestClip * self, gboolean mute)
{
  GList *tmp;

  GST_DEBUG ("self:%p, mute:%d", self, mute);

  self->priv->mute = mute;


  for (tmp = GES_CONTAINER_CHILDREN (self); tmp; tmp = tmp->next) {
    GESTrackElement *trackelement = (GESTrackElement *) tmp->data;

    if (ges_track_element_get_track (trackelement)->type ==
        GES_TRACK_TYPE_AUDIO)
      ges_track_element_set_active (trackelement, !mute);
  }
}
