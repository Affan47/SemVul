sb_rdahead_ctrl( Sockbuf_IO_Desc *sbiod, int opt, void *arg )
{
	Sockbuf_Buf		*p;

	p = (Sockbuf_Buf *)sbiod->sbiod_pvt;

	if ( opt == LBER_SB_OPT_DATA_READY ) {
		if ( p->buf_ptr != p->buf_end ) {
			return 1;
		}

	} else if ( opt == LBER_SB_OPT_SET_READAHEAD ) {
		if ( p->buf_size >= *((ber_len_t *)arg) ) {
			return 0;
		}
		return ( ber_pvt_sb_grow_buffer( p, *((int *)arg) ) ?
			-1 : 1 );
	}

	return LBER_SBIOD_CTRL_NEXT( sbiod, opt, arg );
}
