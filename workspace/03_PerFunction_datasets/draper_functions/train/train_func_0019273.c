gdl_dock_get_property  (GObject      *object,
                        guint         prop_id,
                        GValue       *value,
                        GParamSpec   *pspec)
{
    GdlDock *dock = GDL_DOCK (object);

    switch (prop_id) {
        case PROP_FLOATING:
            g_value_set_boolean (value, dock->_priv->floating);
            break;
        case PROP_DEFAULT_TITLE:
            if (GDL_DOCK_OBJECT (object)->master) {
                gchar *default_title;
                g_object_get (GDL_DOCK_OBJECT (object)->master,
                              "default-title", &default_title,
                              NULL);
#if GLIB_CHECK_VERSION(2,3,0)
                g_value_take_string (value, default_title);
#else
                g_value_set_string_take_ownership (value, default_title);
#endif
            }
            else
                g_value_set_string (value, NULL);
            break;
        case PROP_WIDTH:
            g_value_set_int (value, dock->_priv->width);
            break;
        case PROP_HEIGHT:
            g_value_set_int (value, dock->_priv->height);
            break;
        case PROP_FLOAT_X:
            g_value_set_int (value, dock->_priv->float_x);
            break;
        case PROP_FLOAT_Y:
            g_value_set_int (value, dock->_priv->float_y);
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
    }
}
