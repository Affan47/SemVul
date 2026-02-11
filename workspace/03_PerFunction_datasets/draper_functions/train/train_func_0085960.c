ghes_nmi_add(struct ghes *ghes)
{
	unsigned long len;

	len = ghes_esource_prealloc_size(ghes->generic);
	ghes_estatus_pool_expand(len);
	mutex_lock(&ghes_list_mutex);
	if (list_empty(&ghes_nmi))
		register_nmi_handler(NMI_LOCAL, ghes_notify_nmi, 0, "ghes");
	list_add_rcu(&ghes->list, &ghes_nmi);
	mutex_unlock(&ghes_list_mutex);
}
