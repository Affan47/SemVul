b44_set_flow_ctrl(struct b44 *bp, u32 local, u32 remote)
{
	u32 pause_enab = 0;


	if ((local & ADVERTISE_PAUSE_CAP) &&
	    (local & ADVERTISE_PAUSE_ASYM)){
		if ((remote & LPA_PAUSE_ASYM) &&
		    !(remote & LPA_PAUSE_CAP))
			pause_enab |= B44_FLAG_RX_PAUSE;
	}

	__b44_set_flow_ctrl(bp, pause_enab);
}
