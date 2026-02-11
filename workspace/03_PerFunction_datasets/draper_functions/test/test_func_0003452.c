vrrp_state_handler(vector_t *strvec)
{
	char *str = vector_slot(strvec, 1);
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);
	vrrp_sgroup_t *vgroup = vrrp->sync;

	if (!strcmp(str, "MASTER")) {
		vrrp->wantstate = VRRP_STATE_MAST;
		vrrp->init_state = VRRP_STATE_MAST;
	}


	if (vgroup)
		vgroup->state = vrrp->wantstate;
}
