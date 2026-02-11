sm_check_block(struct sm_ftl *ftl, int zone, int block)
{
	int boffset;
	struct sm_oob oob;
	int lbas[] = { -3, 0, 0, 0 };
	int i = 0;
	int test_lba;


	for (boffset = 0; boffset < ftl->block_size;
					boffset += SM_SECTOR_SIZE) {


		if (sm_read_sector(ftl, zone, block, boffset, NULL, &oob))
			return -2;

		test_lba = sm_read_lba(&oob);

		if (lbas[i] != test_lba)
			lbas[++i] = test_lba;


		if (i == 3)
			return -EIO;
	}


	if (i == 2) {
		sm_erase_block(ftl, zone, block, 1);
		return 1;
	}

	return 0;
}
