undi_unload ( struct undi_device *undi ) {
	static uint32_t dead = 0xdeaddead;

	DBGC ( undi, "UNDI %p unloading\n", undi );


	if ( undi->pxenv.segment )
		put_real ( dead, undi->pxenv.segment, undi->pxenv.offset );
	if ( undi->ppxe.segment )
		put_real ( dead, undi->ppxe.segment, undi->ppxe.offset );


	if ( undi->fbms == get_fbms() ) {
		DBGC ( undi, "UNDI %p freeing [%d,%d) kB of base memory\n",
		       undi, undi->fbms, undi->restore_fbms );
		set_fbms ( undi->restore_fbms );
		return 0;
	} else {
		DBGC ( undi, "UNDI %p leaking [%d,%d) kB of base memory\n",
		       undi, undi->fbms, undi->restore_fbms );
		return -EBUSY;
	}
}
