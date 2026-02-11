sas_queue_work(struct sas_ha_struct *ha, struct sas_work *sw)
{
	if (!test_bit(SAS_HA_REGISTERED, &ha->state))
		return;

	if (test_bit(SAS_HA_DRAINING, &ha->state)) {

		if (list_empty(&sw->drain_node))
			list_add(&sw->drain_node, &ha->defer_q);
	} else
		scsi_queue_work(ha->core.shost, &sw->work);
}
