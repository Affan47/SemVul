use_temporary(struct r300_fragment_program_code *code, unsigned int index)
{
	if (index > code->pixsize)
		code->pixsize = index;
}
