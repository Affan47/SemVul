_create_input_context (IBusIMContext *ibusimcontext)
{
    IDEBUG ("%s", __FUNCTION__);

    g_assert (ibusimcontext->ibuscontext == NULL);

    g_return_if_fail (ibusimcontext->cancellable == NULL);

    ibusimcontext->cancellable = g_cancellable_new ();

    ibus_bus_create_input_context_async (_bus,
            "gtk-im", -1,
            ibusimcontext->cancellable,
            (GAsyncReadyCallback)_create_input_context_done,
            g_object_ref (ibusimcontext));
}
