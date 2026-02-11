monitor_find_children(
	Operation *op,
	SlapReply *rs,
	Entry *e_parent,
	Entry **nonv,
	Entry **vol
)
{
	monitor_entry_t *mp;

	mp = ( monitor_entry_t * )e_parent->e_private;
	*nonv = mp->mp_children;

	if ( MONITOR_HAS_VOLATILE_CH( mp ) ) {
		monitor_entry_create( op, rs, NULL, e_parent, vol );
	}
}
