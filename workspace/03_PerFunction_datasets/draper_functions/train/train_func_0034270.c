has_TC0150ROD(void)
{
	const struct Memory_WriteAddress16 *mwa;


	mwa = Machine->drv->cpu[0].memory_write;
	if (mwa)
	{
		while (!IS_MEMPORT_END(mwa))
		{
			if (!IS_MEMPORT_MARKER(mwa))
			{
				if (mwa->handler == TC0150ROD_word_w)
					return 1;
			}
			mwa++;
		}
	}

	mwa = Machine->drv->cpu[1].memory_write;
	if (mwa)
	{
		while (!IS_MEMPORT_END(mwa))
		{
			if (!IS_MEMPORT_MARKER(mwa))
			{
				if (mwa->handler == TC0150ROD_word_w)
					return 1;
			}
			mwa++;
		}
	}

	mwa = Machine->drv->cpu[2].memory_write;
	if (mwa)
	{
		while (!IS_MEMPORT_END(mwa))
		{
			if (!IS_MEMPORT_MARKER(mwa))
			{
				if (mwa->handler == TC0150ROD_word_w)
					return 1;
			}
			mwa++;
		}
	}

	return 0;
}
