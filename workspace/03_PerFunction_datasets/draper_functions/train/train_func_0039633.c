do_uevent(struct dlm_ls *ls, int in)
{
	int error;

	if (in)
		kobject_uevent(&ls->ls_kobj, KOBJ_ONLINE);
	else
		kobject_uevent(&ls->ls_kobj, KOBJ_OFFLINE);

	log_rinfo(ls, "%s the lockspace group...", in ? "joining" : "leaving");


	error = wait_event_interruptible(ls->ls_uevent_wait,
			test_and_clear_bit(LSFL_UEVENT_WAIT, &ls->ls_flags));

	log_rinfo(ls, "group event done %d %d", error, ls->ls_uevent_result);

	if (error)
		goto out;

	error = ls->ls_uevent_result;
 out:
	if (error)
		log_error(ls, "group %s failed %d %d", in ? "join" : "leave",
			  error, ls->ls_uevent_result);
	return error;
}
