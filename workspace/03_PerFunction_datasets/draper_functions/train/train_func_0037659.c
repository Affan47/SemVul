ges_uri_clip_create_track_element (GESClip * clip, GESTrackType type)
{
  GESUriClipPrivate *priv = GES_URI_CLIP (clip)->priv;
  GESTrackElement *res = NULL;

  if (priv->is_image) {
    if (type != GES_TRACK_TYPE_VIDEO) {
      GST_DEBUG ("Object is still image, not adding any audio source");
      return NULL;
    } else {
      GST_DEBUG ("Creating a GESImageSource");
      res = (GESTrackElement *) ges_image_source_new (priv->uri);
    }

  } else {
    GST_DEBUG ("Creating a GESUriSource");


    if (type == GES_TRACK_TYPE_VIDEO)
      res = (GESTrackElement *) ges_video_uri_source_new (priv->uri);
    else if (type == GES_TRACK_TYPE_AUDIO)
      res = (GESTrackElement *) ges_audio_uri_source_new (priv->uri);


    if (type == GES_TRACK_TYPE_AUDIO && priv->mute)
      ges_track_element_set_active (res, FALSE);
  }

  if (res)
    ges_track_element_set_track_type (res, type);

  return res;
}
