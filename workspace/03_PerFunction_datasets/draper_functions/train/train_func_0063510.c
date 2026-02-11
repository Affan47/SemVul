find_board_by_major(unsigned int major)
{
	unsigned int i;

	for (i = 0; i < MAXBOARDS; i++) {
		struct board_t *brd = dgap_board[i];

		if (!brd)
			return NULL;
		if (major == brd->serial_driver->major ||
		    major == brd->print_driver->major)
			return brd;
	}

	return NULL;
}
