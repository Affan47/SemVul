clear_domain_process_object (GCObject *obj, MonoDomain *domain)
{
	gboolean remove;

	process_object_for_domain_clearing (obj, domain);
	remove = need_remove_object_for_domain (obj, domain);

	if (remove && obj->synchronisation) {
		guint32 dislink = mono_monitor_get_object_monitor_gchandle (obj);
		if (dislink)
			mono_gchandle_free (dislink);
	}

	return remove;
}
