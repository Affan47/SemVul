clutter_im_multicontext_get_slave (ClutterIMMulticontext *multicontext)
{
  if (!multicontext->slave)
    {
      ClutterIMContext *slave;

      if (!global_context_id)
        {
          if (user_context_id)
            global_context_id = user_context_id;
          else
            global_context_id = _clutter_im_module_get_default_context_id ();
        }
      slave = _clutter_im_module_create (global_context_id);
      clutter_im_multicontext_set_slave (multicontext, slave, FALSE);
      g_object_unref (slave);

      g_free (multicontext->context_id);
      multicontext->context_id = g_strdup (global_context_id);
    }

  return multicontext->slave;
}
