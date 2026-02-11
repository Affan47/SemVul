mmc_decode_scr(struct mmc_card *card)
{
	struct sd_scr *scr = &card->scr;
	unsigned int scr_struct;
	u32 resp[4];

	resp[3] = card->raw_scr[1];
	resp[2] = card->raw_scr[0];

	scr_struct = UNSTUFF_BITS(resp, 60, 4);
	if (scr_struct != 0) {
		pr_err("%s: unrecognised SCR structure version %d\n",
			mmc_hostname(card->host), scr_struct);
		return -EINVAL;
	}

	scr->sda_vsn = UNSTUFF_BITS(resp, 56, 4);
	scr->bus_widths = UNSTUFF_BITS(resp, 48, 4);
	if (scr->sda_vsn == SCR_SPEC_VER_2)

		scr->sda_spec3 = UNSTUFF_BITS(resp, 47, 1);

	if (UNSTUFF_BITS(resp, 55, 1))
		card->erased_byte = 0xFF;
	else
		card->erased_byte = 0x0;

	if (scr->sda_spec3)
		scr->cmds = UNSTUFF_BITS(resp, 32, 2);
	return 0;
}
