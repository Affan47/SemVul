vnc_display_set_property (GObject      *object,
                          guint         prop_id,
                          const GValue *value,
                          GParamSpec   *pspec)
{
    VncDisplay *vnc = VNC_DISPLAY (object);

    switch (prop_id)
        {
        case PROP_POINTER_LOCAL:
            vnc_display_set_pointer_local (vnc, g_value_get_boolean (value));
            break;
        case PROP_POINTER_GRAB:
            vnc_display_set_pointer_grab (vnc, g_value_get_boolean (value));
            break;
        case PROP_KEYBOARD_GRAB:
            vnc_display_set_keyboard_grab (vnc, g_value_get_boolean (value));
            break;
        case PROP_READ_ONLY:
            vnc_display_set_read_only (vnc, g_value_get_boolean (value));
            break;
        case PROP_LOSSY_ENCODING:
            vnc_display_set_lossy_encoding (vnc, g_value_get_boolean (value));
            break;
        case PROP_SCALING:
            vnc_display_set_scaling (vnc, g_value_get_boolean (value));
            break;
        case PROP_SHARED_FLAG:
            vnc_display_set_shared_flag (vnc, g_value_get_boolean (value));
            break;
        case PROP_FORCE_SIZE:
            vnc_display_set_force_size (vnc, g_value_get_boolean (value));
            break;
        case PROP_DEPTH:
            vnc_display_set_depth (vnc, g_value_get_enum (value));
            break;
        case PROP_GRAB_KEYS:
            vnc_display_set_grab_keys(vnc, g_value_get_boxed(value));
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
        }
}
