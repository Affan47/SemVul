dlm_event_store(struct dlm_ls *ls, const char *buf, size_t len)
{
	int rc = kstrtoint(buf, 0, &ls->ls_uevent_result);

	if (rc)
		return rc;
	set_bit(LSFL_UEVENT_WAIT, &ls->ls_flags);
	wake_up(&ls->ls_uevent_wait);
	return len;
}
