gupnp_dlna_gst_get_string_value (GstCaps* caps,
                                 GstDiscovererStreamInfo *stream,
                                 GstDiscovererInfo *info,
                                 const gchar *name)
{
        GUPnPDLNAStringValue value = GUPNP_DLNA_STRING_VALUE_UNSET;

        if (caps != NULL) {
                guint caps_size = gst_caps_get_size (caps);
                guint iter;

                for (iter = 0; iter < caps_size; ++iter) {
                        const GstStructure *st = gst_caps_get_structure (caps,
                                                                         iter);

                        value = get_string_value_from_structure (st, name);
                        if (value.state == GUPNP_DLNA_VALUE_STATE_SET)
                                return value;
                }
        }

        if (stream != NULL) {
                const GstStructure *st =
                                   gst_discoverer_stream_info_get_misc (stream);

                value = get_string_value_from_structure (st, name);
                if (value.state == GUPNP_DLNA_VALUE_STATE_SET)
                        return value;
        }

        if (info != NULL) {
                const GstStructure *st = gst_discoverer_info_get_misc (info);

                value = get_string_value_from_structure (st, name);
                if (value.state == GUPNP_DLNA_VALUE_STATE_SET)
                        return value;
        }

        if (stream != NULL) {
                const GstTagList *tags =
                                   gst_discoverer_stream_info_get_tags (stream);

                value = get_string_value_from_tag_list (tags, name);
                if (value.state == GUPNP_DLNA_VALUE_STATE_SET)
                        return value;
        }

        return value;
}
