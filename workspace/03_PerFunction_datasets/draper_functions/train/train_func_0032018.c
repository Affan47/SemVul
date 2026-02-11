brcms_is_mband_unlocked(struct brcms_c_info *wlc)
{
	return wlc->pub->_nbands > 1 && !wlc->bandlocked;
}
