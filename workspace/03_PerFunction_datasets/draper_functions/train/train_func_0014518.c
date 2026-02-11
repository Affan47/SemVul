append_out_of_cycles(struct drccore *drc)
{
	drc_append_save_volatiles(drc);
	if (drc->uses_fp)
	{
		_fnclex();
		_fldcw_m16abs(&drc->fpcw_save);
	}
	_popad();
	_ret();
}
