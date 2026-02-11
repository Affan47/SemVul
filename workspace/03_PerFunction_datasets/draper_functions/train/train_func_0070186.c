gnome_keyring_acl_copy (GList *list)
{
	GList *ret, *l;

	ret = g_list_copy (list);
	for (l = ret; l != NULL; l = l->next) {
		l->data = gnome_keyring_access_control_copy (l->data);
	}

	return ret;
}
