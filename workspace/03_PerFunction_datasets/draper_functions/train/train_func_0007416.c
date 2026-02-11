layer_object_removed_cb (GESTimelineLayer * layer, GESTimelineObject * object,
    GESTimeline * timeline)
{
  GList *tmp, *trackobjects;

  GST_DEBUG ("TimelineObject %p removed from layer %p", object, layer);


  trackobjects = ges_timeline_object_get_track_objects (object);
  for (tmp = trackobjects; tmp; tmp = tmp->next) {
    GESTrackObject *trobj = (GESTrackObject *) tmp->data;

    GST_DEBUG ("Trying to remove TrackObject %p", trobj);
    if (G_LIKELY (g_list_find_custom (timeline->priv->tracks,
                ges_track_object_get_track (trobj),
                (GCompareFunc) custom_find_track))) {
      GST_DEBUG ("Belongs to one of the tracks we control");
      ges_track_remove_object (ges_track_object_get_track (trobj), trobj);

      ges_timeline_object_release_track_object (object, trobj);
    }


    g_object_unref (trobj);
  }
  g_list_free (trackobjects);

  GST_DEBUG ("Done");
}
