assert_triggered(const char *file, uint32_t line)
{
	volatile uint32_t block_var = 0, line_in;
	const char *file_in;


	file_in = file;
	line_in = line;
	(void) file_in;
	(void) line_in;

	taskENTER_CRITICAL();
	{
		while (block_var == 0) {


		}
	}
	taskEXIT_CRITICAL();
}
