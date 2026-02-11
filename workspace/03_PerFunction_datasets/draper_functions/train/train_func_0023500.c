script_uninstantiate(state_t *s, int script_nr)
{
	reg_t reg = make_reg( 0, (s->version < SCI_VERSION_FTU_NEW_SCRIPT_HEADER)? 2 : 0 );
	int i;

	reg.segment = sm_seg_get( &s->seg_manager, script_nr);

	if (!sm_script_is_loaded (&s->seg_manager, script_nr, SCRIPT_ID) || reg.segment <= 0 ) {


		return;
	}

	sm_decrement_lockers( &s->seg_manager, reg.segment, SEG_ID);

	if( sm_get_lockers( &s->seg_manager, reg.segment, SEG_ID) > 0 )
		return;


	for (i = 0; i < s->classtable_size; i++)
		if (s->classtable[i].reg.segment == reg.segment)
			s->classtable[i].reg = NULL_REG;

	if (s->version < SCI_VERSION(1,001,000))
		script_uninstantiate_sci0(s, script_nr, reg.segment);
	else
		sciprintf("FIXME: Add proper script uninstantiation for SCI 1.1\n");

	if( sm_get_lockers( &s->seg_manager, reg.segment, SEG_ID) )
		return;


	sm_mark_script_deleted( &s->seg_manager, script_nr );

	if (script_checkloads_flag)
		sciprintf("Unloaded script 0x%x.\n", script_nr);

	return;
}
