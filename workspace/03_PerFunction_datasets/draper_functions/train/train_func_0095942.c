add_object_to_track (GESTimelineObject * object, GESTrack * track)
{
  if (!ges_timeline_object_create_track_objects (object, track)) {
    GST_WARNING ("error creating track objects");
  }
}
