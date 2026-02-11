entangle_camera_picker_set_property(GObject *object,
                                                guint prop_id,
                                                const GValue *value,
                                                GParamSpec *pspec)
{
    EntangleCameraPicker *picker = ENTANGLE_CAMERA_PICKER(object);

    ENTANGLE_DEBUG("Set prop %d", prop_id);

    switch (prop_id)
        {
        case PROP_CAMERAS:
            entangle_camera_picker_set_camera_list(picker,
                                                   ENTANGLE_CAMERA_LIST(g_value_get_object(value)));
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        }
}
