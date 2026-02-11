osst_write_filemark(struct osst_tape * STp, struct osst_request ** aSRpnt)
{
	int	result;
	int	this_mark_ppos = STp->first_frame_position;
	int	this_mark_lbn  = STp->logical_blk_num;
#if DEBUG
	char  * name = tape_name(STp);
#endif

	if (STp->raw) return 0;

	STp->write_type = OS_WRITE_NEW_MARK;
#if DEBUG
	printk(OSST_DEB_MSG "%s:D: Writing Filemark %i at fppos %d (fseq %d, lblk %d)\n",
	       name, STp->filemark_cnt, this_mark_ppos, STp->frame_seq_number, this_mark_lbn);
#endif
	STp->dirty = 1;
	result  = osst_flush_write_buffer(STp, aSRpnt);
	result |= osst_flush_drive_buffer(STp, aSRpnt);
	STp->last_mark_ppos = this_mark_ppos;
	STp->last_mark_lbn  = this_mark_lbn;
	if (STp->header_cache != NULL && STp->filemark_cnt < OS_FM_TAB_MAX)
		STp->header_cache->dat_fm_tab.fm_tab_ent[STp->filemark_cnt] = htonl(this_mark_ppos);
	if (STp->filemark_cnt++ == 0)
		STp->first_mark_ppos = this_mark_ppos;
	return result;
}
