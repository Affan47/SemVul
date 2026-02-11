cs3_send_lut(cs3_t * s)
{
	int color;
	SANE_Status status;
	cs3_pixel_t *lut, pixel;

	DBG(6, "%s\n", __func__);

	for (color = 0; color < s->n_colors; color++) {


		switch (color) {
		case 0:
			lut = s->lut_r;
			break;
		case 1:
			lut = s->lut_g;
			break;
		case 2:
			lut = s->lut_b;
			break;
		case 3:
			lut = s->lut_neutral;
			break;
		default:
			DBG(1,
			    "BUG: %s: Unknown color number for LUT download.\n",
			    __func__);
			return SANE_STATUS_INVAL;
			break;
		}

		cs3_init_buffer(s);
		cs3_parse_cmd(s, "2a 00 03 00");
		cs3_pack_byte(s, cs3_colors[color]);
		cs3_pack_byte(s, 2 - 1);
		cs3_pack_byte(s, ((2 * s->n_lut) >> 16) & 0xff);
		cs3_pack_byte(s, ((2 * s->n_lut) >> 8) & 0xff);
		cs3_pack_byte(s, (2 * s->n_lut) & 0xff);
		cs3_pack_byte(s, 0x00);

		for (pixel = 0; pixel < s->n_lut; pixel++) {
			cs3_pack_word(s, lut[pixel]);
		}

		status = cs3_issue_cmd(s);
		if (status != SANE_STATUS_GOOD)
			return status;
	}

	return status;
}
