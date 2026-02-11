gkrellm_fs_assign_fsusage_data(gpointer pointer,
			glong blocks, glong bavail, glong bfree, glong bsize)
	{
	Mount	*m = (Mount *) pointer;

	if (   m->blocks != blocks
		|| m->bavail != bavail
		|| m->bfree  != bfree
		|| m->bsize  != bsize
	   )
		{
		m->blocks = blocks;
		m->bavail = bavail;
		m->bfree  = bfree;
		m->bsize  = bsize;

		m->changed = TRUE;
		}
	}
