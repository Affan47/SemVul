uwb_rc_get(struct uwb_rc *rc)
{
	if (rc->ready == 0)
		return NULL;
	uwb_dev_get(&rc->uwb_dev);
	return rc;
}
