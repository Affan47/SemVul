fcoe_fcf_device_add(struct fcoe_ctlr_device *ctlr,
					    struct fcoe_fcf_device *new_fcf)
{
	struct fcoe_fcf_device *fcf;
	int error = 0;

	list_for_each_entry(fcf, &ctlr->fcfs, peers) {
		if (fcoe_fcf_device_match(new_fcf, fcf)) {
			if (fcf->state == FCOE_FCF_STATE_CONNECTED)
				return fcf;

			fcf->state = FCOE_FCF_STATE_CONNECTED;

			if (!cancel_delayed_work(&fcf->dev_loss_work))
				fcoe_ctlr_device_flush_devloss(ctlr);

			return fcf;
		}
	}

	fcf = kzalloc(sizeof(struct fcoe_fcf_device), GFP_ATOMIC);
	if (unlikely(!fcf))
		goto out;

	INIT_WORK(&fcf->delete_work, fcoe_fcf_device_final_delete);
	INIT_DELAYED_WORK(&fcf->dev_loss_work, fip_timeout_deleted_fcf);

	fcf->dev.parent = &ctlr->dev;
	fcf->dev.bus = &fcoe_bus_type;
	fcf->dev.type = &fcoe_fcf_device_type;
	fcf->id = atomic_inc_return(&fcf_num) - 1;
	fcf->state = FCOE_FCF_STATE_UNKNOWN;

	fcf->dev_loss_tmo = ctlr->fcf_dev_loss_tmo;

	dev_set_name(&fcf->dev, "fcf_%d", fcf->id);

	fcf->fabric_name = new_fcf->fabric_name;
	fcf->switch_name = new_fcf->switch_name;
	fcf->fc_map = new_fcf->fc_map;
	fcf->vfid = new_fcf->vfid;
	memcpy(fcf->mac, new_fcf->mac, ETH_ALEN);
	fcf->priority = new_fcf->priority;
	fcf->fka_period = new_fcf->fka_period;
	fcf->selected = new_fcf->selected;

	error = device_register(&fcf->dev);
	if (error)
		goto out_del;

	fcf->state = FCOE_FCF_STATE_CONNECTED;
	list_add_tail(&fcf->peers, &ctlr->fcfs);

	return fcf;

out_del:
	kfree(fcf);
out:
	return NULL;
}
