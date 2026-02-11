alloc_loop_info(void)
{
    Loop_info	*lipt;

    lipt = (Loop_info *)calloc(1, sizeof(Loop_info));
    if (lipt == NULL)
	fatal("No more room for Loop_info.\n");

    lipt->index = NULL;
    lipt->block = NULL;

    return lipt;
}
