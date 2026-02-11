list_names_context_unref (gpointer data)
{
  ListNamesContext *context = data;

  if (--context->refs == 0)
    {
      g_object_unref (context->self);

      if (context->reply != NULL)
        dbus_message_unref (context->reply);

      if (context->destroy != NULL)
        context->destroy (context->user_data);

      context->destroy = NULL;

      if (context->weak_object != NULL)
        g_object_remove_weak_pointer (context->weak_object,
            &context->weak_object);

      g_slice_free (ListNamesContext, context);
    }
}
