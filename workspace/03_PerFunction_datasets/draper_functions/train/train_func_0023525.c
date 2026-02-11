SPI_prepare_params(const char *src,
				   ParserSetupHook parserSetup,
				   void *parserSetupArg,
				   int cursorOptions)
{
	_SPI_plan	plan;
	SPIPlanPtr	result;

	if (src == NULL)
	{
		SPI_result = SPI_ERROR_ARGUMENT;
		return NULL;
	}

	SPI_result = _SPI_begin_call(true);
	if (SPI_result < 0)
		return NULL;

	memset(&plan, 0, sizeof(_SPI_plan));
	plan.magic = _SPI_PLAN_MAGIC;
	plan.cursor_options = cursorOptions;
	plan.nargs = 0;
	plan.argtypes = NULL;
	plan.parserSetup = parserSetup;
	plan.parserSetupArg = parserSetupArg;

	_SPI_prepare_plan(src, &plan);


	result = _SPI_make_plan_non_temp(&plan);

	_SPI_end_call(true);

	return result;
}
