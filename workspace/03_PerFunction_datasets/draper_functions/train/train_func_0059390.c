rd_options(void)
{
	int i, n;

	byte b;

	u16b tmp16u;

	u32b flag[8];
	u32b mask[8];
	u32b window_flag[ANGBAND_TERM_MAX];
	u32b window_mask[ANGBAND_TERM_MAX];


	strip_bytes(16);


	rd_byte(&b);
	op_ptr->delay_factor = b;


	rd_byte(&b);
	op_ptr->hitpoint_warn = b;


	rd_u16b(&tmp16u);
	lazymove_delay = (tmp16u < 1000) ? tmp16u : 0;


	for (n = 0; n < 8; n++) rd_u32b(&flag[n]);


	for (n = 0; n < 8; n++) rd_u32b(&mask[n]);


	for (i = 0; i < OPT_MAX; i++)
	{
		int os = i / 32;
		int ob = i % 32;


		if (mask[os] & (1L << ob))
		{

			if (flag[os] & (1L << ob))
				op_ptr->opt[i] = TRUE;


			else
				op_ptr->opt[i] = FALSE;
		}
	}


	for (n = 0; n < ANGBAND_TERM_MAX; n++)
	{
		rd_u32b(&window_flag[n]);
	}


	for (n = 0; n < ANGBAND_TERM_MAX; n++)
	{
		rd_u32b(&window_mask[n]);
	}


	for (n = 0; n < ANGBAND_TERM_MAX; n++)
	{

		for (i = 0; i < 32; i++)
		{

			if (window_flag_desc[i])
			{

				if (!(window_mask[n] & (1L << i)))
				{
					window_flag[n] &= ~(1L << i);
				}
			}
		}
	}


	subwindows_set_flags(window_flag, ANGBAND_TERM_MAX);

	return 0;
}
