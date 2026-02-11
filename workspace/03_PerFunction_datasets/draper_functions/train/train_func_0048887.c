_mx_entry_icon_motion_event_cb (ClutterActor *actor,
                                ClutterEvent *event,
                                MxEntry      *entry)
{
  MxEntryPrivate *priv = entry->priv;
  MxTooltip *target_tooltip = NULL;
  guint icon_position;

  icon_position = _mx_entry_which_icon (actor, entry);

  if (icon_position  == 1)
    {
      target_tooltip = priv->primary_icon_tooltip;

      _mx_entry_switch_to_highlight_icon (priv->primary_icon,
                                          priv->primary_icon_highlight,
                                          TRUE);
    }
  else if (icon_position == 2)
    {
      target_tooltip = priv->secondary_icon_tooltip;


      _mx_entry_switch_to_highlight_icon (priv->secondary_icon,
                                          priv->secondary_icon_highlight,
                                          TRUE);
    }


  if (target_tooltip && !CLUTTER_ACTOR_IS_VISIBLE (target_tooltip))
    {
      if (mx_tooltip_is_in_browse_mode ())
        {
          mx_tooltip_show (target_tooltip);

          if (priv->tooltip_timeout)
            {
              g_source_remove (priv->tooltip_timeout);
              priv->tooltip_timeout = 0;
            }
        }
      else
        {

          if (!priv->tooltip_timeout)
            priv->tooltip_timeout =
              clutter_threads_add_timeout (MX_ENTRY_TOOLTIP_DELAY,
                                           _mx_entry_tooltip_timeout_cb,
                                           target_tooltip);
        }
    }
  return FALSE;
}
