sm_read_lba(struct sm_oob *oob)
{
	static const uint32_t erased_pattern[4] = {
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

	uint16_t lba_test;
	int lba;


	if (!memcmp(oob, erased_pattern, SM_OOB_SIZE))
		return -1;


	lba_test = *(uint16_t *)oob->lba_copy1 ^ *(uint16_t*)oob->lba_copy2;
	if (lba_test && !is_power_of_2(lba_test))
		return -2;


	lba = sm_get_lba(oob->lba_copy1);

	if (lba == -2)
		lba = sm_get_lba(oob->lba_copy2);

	return lba;
}
