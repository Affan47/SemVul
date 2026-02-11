v_randgen_new(void)
{
	VRandGen	*gen;

	if((gen = malloc(sizeof *gen)) != NULL)
	{
		gen->fd = open(SOURCE, O_RDONLY);
		if(gen->fd < 0)
		{
			fprintf(stderr, __FILE__ ": Couldn't open " SOURCE " for reading\n");
			free(gen);
			gen = NULL;
		}
	}
	return gen;
}
