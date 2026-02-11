internalerrposition(int cursorpos)
{
	ErrorData  *edata = &errordata[errordata_stack_depth];


	CHECK_STACK_DEPTH();

	edata->internalpos = cursorpos;

	return 0;
}
