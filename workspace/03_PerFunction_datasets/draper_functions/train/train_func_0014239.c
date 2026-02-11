e_cal_backend_store_remove_component (ECalBackendStore *store,
                                      const gchar *uid,
                                      const gchar *rid)
{
	ECalBackendStoreClass *class;

	g_return_val_if_fail (E_IS_CAL_BACKEND_STORE (store), FALSE);
	g_return_val_if_fail (uid != NULL, FALSE);

	class = E_CAL_BACKEND_STORE_GET_CLASS (store);
	g_return_val_if_fail (class->remove_component != NULL, FALSE);

	if (class->remove_component (store, uid, rid)) {
		if (e_intervaltree_remove (store->priv->intervaltree, uid, rid))
			return TRUE;
	}

	return FALSE;
}
