exo_icon_view_item_accessible_remove_state (ExoIconViewItemAccessible *item,
                                            AtkStateType               state_type,
                                            gboolean                   emit_signal)
{
  if (atk_state_set_contains_state (item->state_set, state_type))
    {
      gboolean rc;

      rc = atk_state_set_remove_state (item->state_set, state_type);


      if (emit_signal)
        {
          atk_object_notify_state_change (ATK_OBJECT (item), state_type, FALSE);

          if (state_type == ATK_STATE_VISIBLE)
            g_signal_emit_by_name (item, "visible-data-changed");
        }

      return rc;
    }
  else
    return FALSE;
}
