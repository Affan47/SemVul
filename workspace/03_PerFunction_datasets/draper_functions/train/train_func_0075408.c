collect_swp(swp_stat *s UNUSED_PARAM)
{
	ullong s_total[1];
	ullong s_free[1];
	if (rdval(get_file(&proc_meminfo), "SwapTotal:", s_total, 1)
	 || rdval(proc_meminfo.file,       "SwapFree:" , s_free,  1)
	) {
		put_question_marks(4);
		return;
	}
	scale((s_total[0]-s_free[0]) << 10);
}
