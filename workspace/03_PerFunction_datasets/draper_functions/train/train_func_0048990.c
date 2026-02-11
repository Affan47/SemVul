_child_clip_changed_layer_cb (GESTimelineElement * clip,
    GParamSpec * arg G_GNUC_UNUSED, GESGroup * group)
{
  gint offset, layer_prio = ges_clip_get_layer_priority (GES_CLIP (clip));
  GESContainer *container = GES_CONTAINER (group);

  if (container->children_control_mode != GES_CHILDREN_UPDATE) {
    if (container->children_control_mode == GES_CHILDREN_INIBIT_SIGNAL_EMISSION) {
      container->children_control_mode = GES_CHILDREN_UPDATE;
      g_signal_stop_emission_by_name (clip, "notify::layer");
    }
    return;
  }

  offset = _ges_container_get_priority_offset (container, clip);

  if (layer_prio + offset < 0 ||
      (GES_TIMELINE_ELEMENT_TIMELINE (group) &&
          layer_prio + offset + GES_CONTAINER_HEIGHT (group) - 1 >
          g_list_length (GES_TIMELINE_ELEMENT_TIMELINE (group)->layers))) {
    GESLayer *old_layer =
        g_list_nth_data (GES_TIMELINE_ELEMENT_TIMELINE (group)->layers,
        _PRIORITY (group) - offset);

    GST_INFO_OBJECT (container, "Trying to move to a layer outside of"
        "the timeline layers, moving back to old layer (prio %i)",
        _PRIORITY (group) - offset);

    container->children_control_mode = GES_CHILDREN_INIBIT_SIGNAL_EMISSION;
    ges_clip_move_to_layer (GES_CLIP (clip), old_layer);
    g_signal_stop_emission_by_name (clip, "notify::layer");

    return;
  }

  container->initiated_move = clip;
  _set_priority0 (GES_TIMELINE_ELEMENT (group), layer_prio + offset);
  container->initiated_move = NULL;
}
