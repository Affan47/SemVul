fixup_quotation(F_QUOTATION *quot)
{
	if(quot->compiledp == F)
		quot->xt = lazy_jit_compile;
	else
	{
		code_fixup((CELL)&quot->xt);
		code_fixup((CELL)&quot->code);
	}
}
