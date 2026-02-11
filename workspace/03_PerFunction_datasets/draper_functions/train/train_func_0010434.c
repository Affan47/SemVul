primitive_fflush(void)
{
	FILE *file = unbox_alien();
	for(;;)
	{
		if(fflush(file) == EOF)
			io_error();
		else
			break;
	}
}
