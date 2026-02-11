set_ibus_engine_finish (GObject            *object,
                        GAsyncResult       *res,
                        GsdKeyboardManager *manager)
{
        gboolean result;
        IBusBus *ibus = IBUS_BUS (object);
        GsdKeyboardManagerPrivate *priv = manager->priv;
        GError *error = NULL;

        g_clear_object (&priv->ibus_cancellable);

        result = ibus_bus_set_global_engine_async_finish (ibus, res, &error);
        if (!result) {
                if (!g_error_matches (error, G_IO_ERROR, G_IO_ERROR_CANCELLED))
                        g_warning ("Couldn't set IBus engine: %s", error->message);
                g_error_free (error);
                return;
        }

        maybe_return_from_set_input_source (manager);
}
