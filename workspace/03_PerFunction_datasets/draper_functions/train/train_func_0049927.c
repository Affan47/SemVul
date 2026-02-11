display_player_sust_info(void)
{
	int i, row, col, stat;

	object_type *o_ptr;
	bitflag f[OF_SIZE];

	int stat_flags[A_MAX];
	int sustain_flags[A_MAX];

	byte a;
	char c;


	row = 2;


	col = 26;


	stat_flags[A_STR] = OF_STR;
	stat_flags[A_INT] = OF_INT;
	stat_flags[A_WIS] = OF_WIS;
	stat_flags[A_DEX] = OF_DEX;
	stat_flags[A_CON] = OF_CON;
	stat_flags[A_CHR] = OF_CHR;
	sustain_flags[A_STR] = OF_SUST_STR;
	sustain_flags[A_INT] = OF_SUST_INT;
	sustain_flags[A_WIS] = OF_SUST_WIS;
	sustain_flags[A_DEX] = OF_SUST_DEX;
	sustain_flags[A_CON] = OF_SUST_CON;
	sustain_flags[A_CHR] = OF_SUST_CHR;


	c_put_str(TERM_WHITE, "abcdefghijkl@", row-1, col);


	for (i = INVEN_WIELD; i < INVEN_TOTAL; ++i)
	{

		o_ptr = &inventory[i];


		object_flags_known(o_ptr, f);


		for (stat = 0; stat < A_MAX; stat++)
		{

			a = TERM_SLATE;
			c = '.';


			if (of_has(f, stat_flags[stat]))
			{

				c = '*';


				if (o_ptr->pval > 0)
				{

					a = TERM_L_GREEN;


					if (o_ptr->pval < 10) c = I2D(o_ptr->pval);
				}


				if (o_ptr->pval < 0)
				{

					a = TERM_RED;


					if (o_ptr->pval > -10) c = I2D(-(o_ptr->pval));
				}
			}


			if (of_has(f, sustain_flags[stat]))
			{

				a = TERM_GREEN;


				if (c == '.') c = 's';
			}

			if ((c == '.') && o_ptr->k_idx && !object_flag_is_known(o_ptr, sustain_flags[stat]))
				c = '?';


			Term_putch(col, row+stat, a, c);
		}


		col++;
	}


	player_flags(f);


	for (stat = 0; stat < A_MAX; ++stat)
	{

		a = TERM_SLATE;
		c = '.';


		if (of_has(f, sustain_flags[stat]))
		{

			a = TERM_GREEN;
			c = 's';
		}


		Term_putch(col, row+stat, a, c);
	}


	col = 26;


	c_put_str(TERM_WHITE, "abcdefghijkl@", row+6, col);


	display_player_equippy(row+7, col);
}
