bb_link (MonoSimpleBasicBlock *from, MonoSimpleBasicBlock *to)
{
	if (g_slist_find (from->out_bb, to))
		return;
	from->out_bb = g_slist_prepend (from->out_bb, to);
}
