fcoe_transport_attach(struct fcoe_transport *ft)
{
	int rc = 0;

	mutex_lock(&ft_mutex);
	if (ft->attached) {
		LIBFCOE_TRANSPORT_DBG("transport %s already attached\n",
				       ft->name);
		rc = -EEXIST;
		goto out_attach;
	}


	if (strcmp(ft->name, FCOE_TRANSPORT_DEFAULT))
		list_add(&ft->list, &fcoe_transports);
	else
		list_add_tail(&ft->list, &fcoe_transports);

	ft->attached = true;
	LIBFCOE_TRANSPORT_DBG("attaching transport %s\n", ft->name);

out_attach:
	mutex_unlock(&ft_mutex);
	return rc;
}
