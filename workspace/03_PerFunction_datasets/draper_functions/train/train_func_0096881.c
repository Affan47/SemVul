Solveable()
	{
		for (int i = 0; i < BOXES; ++i)
		{
			if (item[i].val < 0 && item[i].poss.num() == 0)
				return false;
		}

		for (int bb = 0; bb < BIGBOXES; ++bb)
		{
			const unsigned int bbcol = (bb % 3);
			const unsigned int bbrow = (bb / 3);
			const unsigned int bbstart = bbrow * 27 + bbcol * 3;
			Possible<int,9> possible;
			possible.clear();
			for (int r = 0; r < 3; ++r)
			{
				for (int c = 0; c < 3; ++c)
				{
					possible |= item[bbstart + r * COLS + c].poss;


				}
			}


			if (bigbox[bb].num() > (possible & bigbox[bb]).num())
				return false;
		}
		for (int c = 0; c < COLS; ++c)
		{
			Possible<int,9> possible;
			possible.clear();

			for (int r = 0; r < ROWS; ++r)
			{
				possible |= item[c + r * COLS].poss;
			}
			if (col[c].num() > (possible & col[c]).num())
				return false;
		}
		for (int r = 0; r < ROWS; ++r)
		{
			Possible<int,9> possible;
			possible.clear();
			unsigned int rowstart = r * COLS;
			for (int c = 0; c < ROWS; ++c)
			{
				possible |= item[c + rowstart].poss;
			}
			if (row[r].num() > (possible & row[r]).num())
				return false;
		}
		return true;
	}
