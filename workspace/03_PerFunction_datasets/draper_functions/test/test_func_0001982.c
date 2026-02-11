dlm_slot_save(struct dlm_ls *ls, struct dlm_rcom *rc,
		   struct dlm_member *memb)
{
	struct rcom_config *rf = (struct rcom_config *)rc->rc_buf;

	if (!dlm_slots_version(&rc->rc_header))
		return;

	memb->slot = le16_to_cpu(rf->rf_our_slot);
	memb->generation = le32_to_cpu(rf->rf_generation);
}
