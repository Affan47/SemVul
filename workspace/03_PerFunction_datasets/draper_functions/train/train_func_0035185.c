vrrp_init_script(list l)
{
	vrrp_script_t *vscript;
	element e;

	for (e = LIST_HEAD(l); e; ELEMENT_NEXT(e)) {
		vscript = ELEMENT_DATA(e);
		if (vscript->inuse == 0)
			vscript->result = VRRP_SCRIPT_STATUS_DISABLED;

		if (vscript->result == VRRP_SCRIPT_STATUS_INIT) {
			vscript->result = vscript->rise - 1;
			thread_add_event(master, vrrp_script_thread, vscript, vscript->interval);
		} else if (vscript->result == VRRP_SCRIPT_STATUS_INIT_GOOD) {
			vscript->result = vscript->rise;
			thread_add_event(master, vrrp_script_thread, vscript, vscript->interval);
		}
	}
}
