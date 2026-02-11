spi_atk_tidy_windows (void)
{
  AtkObject *root;
  gint n_children;
  gint i;

  root = atk_get_root ();
  n_children = atk_object_get_n_accessible_children (root);
  for (i = 0; i < n_children; i++)
    {
      AtkObject *child;
      AtkStateSet *stateset;
      const gchar *name;

      child = atk_object_ref_accessible_child (root, i);
      stateset = atk_object_ref_state_set (child);

      name = atk_object_get_name (child);
      if (atk_state_set_contains_state (stateset, ATK_STATE_ACTIVE))
        {
          emit_event (child, ITF_EVENT_WINDOW, "deactivate", NULL, 0, 0,
                      DBUS_TYPE_STRING_AS_STRING, name, append_basic);
        }
      g_object_unref (stateset);

      emit_event (child, ITF_EVENT_WINDOW, "destroy", NULL, 0, 0,
                  DBUS_TYPE_STRING_AS_STRING, name, append_basic);
      g_object_unref (child);
    }
}
