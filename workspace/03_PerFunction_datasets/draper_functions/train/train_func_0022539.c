tp_connection_manager_ready_cb (GObject *source_object,
    GAsyncResult *res,
    gpointer user_data)
{
  WhenReadyContext *c = user_data;
  GError *error = NULL;
  GObject *weak_object = NULL;

  g_return_if_fail (source_object == (GObject *) c->cm);

  if (c->weak_ref != NULL)
    {
      weak_object = tp_weak_ref_dup_object (c->weak_ref);

      if (weak_object == NULL)
        goto finally;
    }

  if (tp_proxy_prepare_finish (source_object, res, &error))
    {
      c->callback (c->cm, NULL, c->user_data, weak_object);
    }
  else
    {
      g_assert (error != NULL);
      c->callback (c->cm, error, c->user_data, weak_object);
      g_error_free (error);
    }

finally:
  if (weak_object != NULL)
    g_object_unref (weak_object);

  when_ready_context_free (c);
}
