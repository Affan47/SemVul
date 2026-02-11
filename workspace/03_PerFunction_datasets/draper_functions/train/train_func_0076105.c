parse_one_option (gint opt, const gchar * arg, GError ** err)
{
  switch (opt) {
    case ARG_VERSION:
      g_print ("GStreamer Core Library version %s\n", PACKAGE_VERSION);
      exit (0);
    case ARG_FATAL_WARNINGS:{
      GLogLevelFlags fatal_mask;

      fatal_mask = g_log_set_always_fatal (G_LOG_FATAL_MASK);
      fatal_mask |= G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL;
      g_log_set_always_fatal (fatal_mask);
      break;
    }
#ifndef GST_DISABLE_GST_DEBUG
    case ARG_DEBUG_LEVEL:{
      GstDebugLevel tmp = GST_LEVEL_NONE;

      tmp = (GstDebugLevel) strtol (arg, NULL, 0);
      if (((guint) tmp) < GST_LEVEL_COUNT) {
        gst_debug_set_default_threshold (tmp);
      }
      break;
    }
    case ARG_DEBUG:
      gst_debug_set_threshold_from_string (arg, FALSE);
      break;
    case ARG_DEBUG_NO_COLOR:
      gst_debug_set_colored (FALSE);
      break;
    case ARG_DEBUG_COLOR_MODE:
      gst_debug_set_color_mode_from_string (arg);
      break;
    case ARG_DEBUG_DISABLE:
      gst_debug_set_active (FALSE);
      break;
    case ARG_DEBUG_HELP:
      gst_debug_help ();
      exit (0);
#endif
    case ARG_PLUGIN_SPEW:
      break;
    case ARG_PLUGIN_PATH:
#ifndef GST_DISABLE_REGISTRY
      split_and_iterate (arg, G_SEARCHPATH_SEPARATOR_S, add_path_func, NULL);
#endif
      break;
    case ARG_PLUGIN_LOAD:
      split_and_iterate (arg, ",", prepare_for_load_plugin_func, NULL);
      break;
    case ARG_SEGTRAP_DISABLE:
      _gst_disable_segtrap = TRUE;
      break;
    case ARG_REGISTRY_UPDATE_DISABLE:
#ifndef GST_DISABLE_REGISTRY
      _priv_gst_disable_registry_update = TRUE;
#endif
      break;
    case ARG_REGISTRY_FORK_DISABLE:
      gst_registry_fork_set_enabled (FALSE);
      break;
    default:
      g_set_error (err, G_OPTION_ERROR, G_OPTION_ERROR_UNKNOWN_OPTION,
          _("Unknown option"));
      return FALSE;
  }

  return TRUE;
}
