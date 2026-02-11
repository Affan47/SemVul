ibus_im_context_set_client_window (GtkIMContext *context, GdkWindow *client)
{
    IDEBUG ("%s", __FUNCTION__);

    IBusIMContext *ibusimcontext = IBUS_IM_CONTEXT (context);

    if (ibusimcontext->client_window) {
        g_object_unref (ibusimcontext->client_window);
        ibusimcontext->client_window = NULL;
    }

    if (client != NULL)
        ibusimcontext->client_window = g_object_ref (client);

    if (ibusimcontext->slave)
        gtk_im_context_set_client_window (ibusimcontext->slave, client);
}
