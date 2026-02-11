k_slock(struct vc_data *vc, unsigned char value, char up_flag)
{
	k_shift(vc, value, up_flag);
	if (up_flag || rep)
		return;

	chg_vc_kbd_slock(kbd, value);

	if (!key_maps[kbd->lockstate ^ kbd->slockstate]) {
		kbd->slockstate = 0;
		chg_vc_kbd_slock(kbd, value);
	}
}
