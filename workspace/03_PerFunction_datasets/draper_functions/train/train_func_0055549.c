wireless_dialog_closure_closure_notify (gpointer data,
                                        GClosure *gclosure)
{
        WirelessDialogClosure *closure = data;
        g_object_unref (closure->client);
        g_object_unref (closure->settings);

        g_slice_free (WirelessDialogClosure, data);
}
