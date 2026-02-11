SPI_execute(const char *src, bool read_only, long tcount)
{
	_SPI_plan	plan;
	int			res;

	if (src == NULL || tcount < 0)
		return SPI_ERROR_ARGUMENT;

	res = _SPI_begin_call(true);
	if (res < 0)
		return res;

	memset(&plan, 0, sizeof(_SPI_plan));
	plan.magic = _SPI_PLAN_MAGIC;
	plan.cursor_options = 0;

	_SPI_prepare_plan(src, &plan, NULL);

	res = _SPI_execute_plan(&plan, NULL,
							InvalidSnapshot, InvalidSnapshot,
							read_only, true, tcount);

	_SPI_end_call(true);
	return res;
}
