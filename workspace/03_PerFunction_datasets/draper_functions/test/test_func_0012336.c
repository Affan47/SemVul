be_entry_release_rw(
	Operation *op,
	Entry *e,
	int rw )
{
	if ( op->o_bd->be_release ) {

		return op->o_bd->be_release( op, e, rw );
	} else {

		entry_free( e );
		return 0;
	}
}
