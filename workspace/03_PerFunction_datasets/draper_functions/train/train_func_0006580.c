gf_sc_set_size(GF_Compositor *compositor, u32 NewWidth, u32 NewHeight)
{
	Bool lock_ok;
	if (!NewWidth || !NewHeight) {
		compositor->override_size_flags &= ~2;
		return GF_OK;
	}


	lock_ok = gf_mx_try_lock(compositor->mx);

	compositor->new_width = NewWidth;
	compositor->new_height = NewHeight;
	compositor->msg_type |= GF_SR_CFG_SET_SIZE;


	compositor->msg_type &= ~GF_SR_CFG_WINDOWSIZE_NOTIF;
	if ((compositor->display_width == NewWidth) && (compositor->display_height == NewHeight) ) {
		compositor->msg_type |= GF_SR_CFG_WINDOWSIZE_NOTIF;
	}
	if (lock_ok) gf_sc_lock(compositor, 0);

	return GF_OK;
}
