gsm_store_clear (GsmStore *store)
{
        g_return_if_fail (store != NULL);

        g_debug ("GsmStore: Clearing object store");

        gsm_store_foreach_remove (store,
                                  _remove_all,
                                  NULL);
}
