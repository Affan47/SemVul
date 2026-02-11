connection_held_handles (TpConnection *self,
                         const GError *error,
                         gpointer user_data,
                         GObject *weak_object)
{
  HoldHandlesContext *context = user_data;

  g_object_ref (self);

  if (error == NULL)
    {
      DEBUG ("%u handles of type %u", context->handles->len,
          context->handle_type);


      context->callback (self, context->handle_type, context->handles->len,
          (const TpHandle *) context->handles->data, NULL,
          context->user_data, weak_object);
    }
  else
    {
      DEBUG ("%u handles of type %u failed: %s %u: %s",
          context->handles->len, context->handle_type,
          g_quark_to_string (error->domain), error->code, error->message);
      context->callback (self, context->handle_type, 0, NULL, error,
          context->user_data, weak_object);
    }

  g_object_unref (self);
}
