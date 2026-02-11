__res_iclose(res_state statp, bool free_addr) {
	int ns;

	if (statp->_vcsock >= 0) {
		close_not_cancel_no_status(statp->_vcsock);
		statp->_vcsock = -1;
		statp->_flags &= ~(RES_F_VC | RES_F_CONN);
	}
#ifdef _LIBC
	for (ns = 0; ns < MAXNS; ns++)
#else
	for (ns = 0; ns < statp->_u._ext.nscount; ns++)
#endif
		if (statp->_u._ext.nsaddrs[ns]) {
			if (statp->_u._ext.nssocks[ns] != -1) {
				close_not_cancel_no_status(statp->_u._ext.nssocks[ns]);
				statp->_u._ext.nssocks[ns] = -1;
			}
			if (free_addr) {
				free (statp->_u._ext.nsaddrs[ns]);
				statp->_u._ext.nsaddrs[ns] = NULL;
			}
		}
	statp->_u._ext.nsinit = 0;
}
