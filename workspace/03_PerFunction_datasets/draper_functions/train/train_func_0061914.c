ctlr_snap_buffer_sscp_lu(void)
{
	register int	baddr = 0;


	do {
	    	if (ea_buf[baddr].cc == 0xff) {
			space3270out(1);
			*obptr++ = 0xff;
		}
		space3270out(1);
		*obptr++ = ea_buf[baddr].cc;
		INC_BA(baddr);
	} while (baddr != 0);


	if (cursor_addr != baddr) {
		do {
			if (ea_buf[baddr].cc == 0xff) {
				space3270out(1);
				*obptr++ = 0xff;
			}
			space3270out(1);
			*obptr++ = ea_buf[baddr].cc;
			INC_BA(baddr);
		} while (baddr != cursor_addr);
	}
}
