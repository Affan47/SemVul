clutter_text_key_press (ClutterActor    *actor,
                        ClutterKeyEvent *event)
{
  ClutterText *self = CLUTTER_TEXT (actor);
  ClutterTextPrivate *priv = self->priv;
  ClutterBindingPool *pool;
  gboolean res;

  if (!priv->editable)
    return CLUTTER_EVENT_PROPAGATE;


  pool = clutter_binding_pool_find (g_type_name (CLUTTER_TYPE_TEXT));
  g_assert (pool != NULL);


  if (event->keyval == 0 && (event->flags & CLUTTER_EVENT_FLAG_SYNTHETIC))
    res = FALSE;
  else
    res = clutter_binding_pool_activate (pool, event->keyval,
                                         event->modifier_state,
                                         G_OBJECT (actor));


  if (res)
    return CLUTTER_EVENT_STOP;
  else if ((event->modifier_state & CLUTTER_CONTROL_MASK) == 0)
    {
      gunichar key_unichar;


      key_unichar = clutter_event_get_key_unicode ((ClutterEvent *) event);


      if (key_unichar == '\r')
        key_unichar = '\n';

      if ((key_unichar == '\n' && !priv->single_line_mode) ||
          (g_unichar_validate (key_unichar) &&
           !g_unichar_iscntrl (key_unichar)))
        {


          clutter_text_delete_selection (self);
          clutter_text_insert_unichar (self, key_unichar);

          if (priv->show_password_hint)
            {
              if (priv->password_hint_id != 0)
                g_source_remove (priv->password_hint_id);

              priv->password_hint_visible = TRUE;
              priv->password_hint_id =
                clutter_threads_add_timeout (priv->password_hint_timeout,
                                             clutter_text_remove_password_hint,
                                             self);
            }

          return CLUTTER_EVENT_STOP;
        }
    }

  return CLUTTER_EVENT_PROPAGATE;
}
