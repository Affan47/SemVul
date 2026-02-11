discover_closure_free (gpointer data)
{
        DiscoverClosure *discover = data;
        g_object_unref (discover->manager);
        g_clear_object (&discover->cancellable);
        g_list_free_full (discover->realms, g_object_unref);
        g_slice_free (DiscoverClosure, discover);
}
