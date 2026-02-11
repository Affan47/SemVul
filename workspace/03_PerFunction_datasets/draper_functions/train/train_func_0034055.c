add_param_basic (DBusMessageIter *iter_array,
                 const char      *name,
                 int              type,
                 const void      *value)
{
        DBusMessageIter iter_struct;
        DBusMessageIter iter_variant;
        const char     *container_type;

        switch (type) {
        case DBUS_TYPE_STRING:
                container_type = DBUS_TYPE_STRING_AS_STRING;
                break;
        case DBUS_TYPE_BOOLEAN:
                container_type = DBUS_TYPE_BOOLEAN_AS_STRING;
                break;
        case DBUS_TYPE_INT32:
                container_type = DBUS_TYPE_INT32_AS_STRING;
                break;
        default:
                goto oom;
                break;
        }

        if (! dbus_message_iter_open_container (iter_array,
                                                DBUS_TYPE_STRUCT,
                                                NULL,
                                                &iter_struct)) {
                goto oom;
        }

        if (! dbus_message_iter_append_basic (&iter_struct,
                                              DBUS_TYPE_STRING,
                                              &name)) {
                goto oom;
        }

        if (! dbus_message_iter_open_container (&iter_struct,
                                                DBUS_TYPE_VARIANT,
                                                container_type,
                                                &iter_variant)) {
                goto oom;
        }

        if (! dbus_message_iter_append_basic (&iter_variant,
                                              type,
                                              value)) {
                goto oom;
        }

        if (! dbus_message_iter_close_container (&iter_struct,
                                                 &iter_variant)) {
                goto oom;
        }

        if (! dbus_message_iter_close_container (iter_array,
                                                 &iter_struct)) {
                goto oom;
        }

        return TRUE;
oom:
        return FALSE;
}
