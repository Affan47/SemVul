gclue_locator_stop (GClueLocator        *locator,
                    GCancellable        *cancellable,
                    GAsyncReadyCallback  callback,
                    gpointer             user_data)
{
        GSimpleAsyncResult *simple;

        g_return_if_fail (GCLUE_IS_LOCATOR (locator));

        gclue_locator_stop_sync (locator);

        simple = g_simple_async_result_new (G_OBJECT (locator),
                                            callback,
                                            user_data,
                                            gclue_locator_stop);
        g_simple_async_result_complete_in_idle (simple);

        g_object_unref (simple);
}
