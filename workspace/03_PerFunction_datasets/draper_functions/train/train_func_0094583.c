e_contact_store_find_contact (EContactStore *contact_store,
                              const gchar *uid,
                              GtkTreeIter *iter)
{
	gint index;

	g_return_val_if_fail (E_IS_CONTACT_STORE (contact_store), FALSE);
	g_return_val_if_fail (uid != NULL, FALSE);

	index = find_contact_by_uid (contact_store, uid);
	if (index < 0)
		return FALSE;

	ITER_SET (contact_store, iter, index);
	return TRUE;
}
