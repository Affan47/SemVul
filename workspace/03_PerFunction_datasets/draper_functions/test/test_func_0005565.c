get_property (GObject    *object,
              guint       prop_id,
              GValue     *value,
              GParamSpec *pspec)
{
    CutRunContextPrivate *priv = CUT_RUN_CONTEXT_GET_PRIVATE(object);

    switch (prop_id) {
      case PROP_N_TESTS:
        g_value_set_uint(value, priv->n_tests);
        break;
      case PROP_N_ASSERTIONS:
        g_value_set_uint(value, priv->n_assertions);
        break;
      case PROP_N_SUCCESSES:
        g_value_set_uint(value, priv->n_successes);
        break;
      case PROP_N_FAILURES:
        g_value_set_uint(value, priv->n_failures);
        break;
      case PROP_N_ERRORS:
        g_value_set_uint(value, priv->n_errors);
        break;
      case PROP_N_PENDINGS:
        g_value_set_uint(value, priv->n_pendings);
        break;
      case PROP_N_NOTIFICATIONS:
        g_value_set_uint(value, priv->n_notifications);
        break;
      case PROP_N_OMISSIONS:
        g_value_set_uint(value, priv->n_omissions);
        break;
      case PROP_USE_MULTI_THREAD:
        g_value_set_boolean(value, priv->use_multi_thread);
        break;
      case PROP_IS_MULTI_THREAD:
        g_value_set_boolean(value, priv->is_multi_thread);
        break;
      case PROP_MAX_THREADS:
        g_value_set_int(value, priv->max_threads);
        break;
      case PROP_HANDLE_SIGNALS:
        g_value_set_boolean(value, priv->handle_signals);
        break;
      case PROP_TEST_CASE_ORDER:
        g_value_set_enum(value, priv->test_case_order);
        break;
      case PROP_TEST_DIRECTORY:
        g_value_set_string(value, priv->test_directory);
        break;
      case PROP_SOURCE_DIRECTORY:
        g_value_set_string(value, priv->source_directory);
        break;
      case PROP_LOG_DIRECTORY:
        g_value_set_string(value, priv->log_directory);
        break;
      case PROP_TARGET_TEST_CASE_NAMES:
        g_value_set_pointer(value, priv->target_test_case_names);
        break;
      case PROP_TARGET_TEST_NAMES:
        g_value_set_pointer(value, priv->target_test_names);
        break;
      case PROP_EXCLUDE_FILES:
        g_value_set_pointer(value, priv->exclude_files);
        break;
      case PROP_EXCLUDE_DIRECTORIES:
        g_value_set_pointer(value, priv->exclude_directories);
        break;
      case PROP_COMMAND_LINE_ARGS:
        g_value_set_pointer(value, priv->command_line_args);
        break;
      case PROP_FATAL_FAILURES:
        g_value_set_boolean(value, priv->fatal_failures);
        break;
      case PROP_KEEP_OPENING_MODULES:
        g_value_set_boolean(value, priv->keep_opening_modules);
        break;
      case PROP_ENABLE_CONVENIENCE_ATTRIBUTE_DEFINITION:
        g_value_set_boolean(value, priv->enable_convenience_attribute_definition);
        break;
      case PROP_STOP_BEFORE_TEST:
        g_value_set_boolean(value, priv->stop_before_test);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
