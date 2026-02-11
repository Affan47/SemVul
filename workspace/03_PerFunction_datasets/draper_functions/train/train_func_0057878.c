__do_st_disc_and_login(struct discovery_rec *drec)
{
	struct list_head rec_list, setup_ifaces;
	struct iface_rec *iface, *tmp_iface;
	int rc;

	INIT_LIST_HEAD(&rec_list);
	INIT_LIST_HEAD(&setup_ifaces);


	drec->u.sendtargets.reopen_max = 0;

	iface_link_ifaces(&setup_ifaces);


	ipc = NULL;

	rc = idbm_bind_ifaces_to_nodes(discovery_sendtargets, drec,
					&setup_ifaces, &rec_list);
	if (rc) {
		log_error("Could not perform SendTargets to %s:%d.",
			   drec->address, drec->port);
		goto free_ifaces;
	}

	update_sessions(&rec_list, NULL, NULL);

free_ifaces:
	list_for_each_entry_safe(iface, tmp_iface, &setup_ifaces, list) {
		list_del(&iface->list);
		free(iface);
	}
}
