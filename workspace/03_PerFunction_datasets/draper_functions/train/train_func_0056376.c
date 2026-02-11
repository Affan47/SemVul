alua_bus_detach(struct scsi_device *sdev)
{
	struct alua_dh_data *h = sdev->handler_data;
	struct alua_port_group *pg;

	spin_lock(&h->pg_lock);
	pg = h->pg;
	rcu_assign_pointer(h->pg, NULL);
	h->sdev = NULL;
	spin_unlock(&h->pg_lock);
	if (pg)
		kref_put(&pg->kref, release_port_group);

	sdev->handler_data = NULL;
	kfree(h);
}
