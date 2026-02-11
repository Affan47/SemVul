fcoe_ctlr_set_state(struct fcoe_ctlr *fip, enum fip_state state)
{
	if (state == fip->state)
		return;
	if (fip->lp)
		LIBFCOE_FIP_DBG(fip, "state %s -> %s\n",
			fcoe_ctlr_state(fip->state), fcoe_ctlr_state(state));
	fip->state = state;
}
