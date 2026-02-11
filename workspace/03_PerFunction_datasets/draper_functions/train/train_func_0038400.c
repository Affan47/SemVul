parse_timeline_markers (JsonArray *array,
                        guint      index_,
                        JsonNode  *element,
                        gpointer   data)
{
  ParseClosure *clos = data;
  JsonObject *object;
  TimelineMarker *marker;
  GList *markers;

  if (JSON_NODE_TYPE (element) != JSON_NODE_OBJECT)
    {
      g_warning ("The 'markers' member of a ClutterTimeline description "
                 "should be an array of objects, but the element %d of the "
                 "array is of type '%s'. The element will be ignored.",
                 index_,
                 json_node_type_name (element));
      return;
    }

  object = json_node_get_object (element);

  if (!(json_object_has_member (object, "name") &&
        (json_object_has_member (object, "time") ||
         json_object_has_member (object, "progress"))))
    {
      g_warning ("The marker definition in a ClutterTimeline description "
                 "must be an object with the 'name' and either the 'time' "
                 "or the 'progress' members, but the element %d of the "
                 "'markers' array does not have any of them.",
                 index_);
      return;
    }

  if (G_IS_VALUE (clos->value))
    markers = g_value_get_pointer (clos->value);
  else
    {
      g_value_init (clos->value, G_TYPE_POINTER);
      markers = NULL;
    }

  if (json_object_has_member (object, "time"))
    marker = timeline_marker_new_time (json_object_get_string_member (object, "name"),
                                       json_object_get_int_member (object, "time"));
  else
    marker = timeline_marker_new_progress (json_object_get_string_member (object, "name"),
                                           json_object_get_double_member (object, "progress"));

  markers = g_list_prepend (markers, marker);

  g_value_set_pointer (clos->value, markers);

  clos->result = TRUE;
}
