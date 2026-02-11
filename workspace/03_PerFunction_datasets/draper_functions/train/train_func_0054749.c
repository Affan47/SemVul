configure_custom_video_timings(struct v4l2_subdev *sd,
		const struct v4l2_bt_timings *bt)
{
	struct adv76xx_state *state = to_state(sd);
	u32 width = htotal(bt);
	u32 height = vtotal(bt);
	u16 cp_start_sav = bt->hsync + bt->hbackporch - 4;
	u16 cp_start_eav = width - bt->hfrontporch;
	u16 cp_start_vbi = height - bt->vfrontporch;
	u16 cp_end_vbi = bt->vsync + bt->vbackporch;
	u16 ch1_fr_ll = (((u32)bt->pixelclock / 100) > 0) ?
		((width * (ADV76XX_FSC / 100)) / ((u32)bt->pixelclock / 100)) : 0;
	const u8 pll[2] = {
		0xc0 | ((width >> 8) & 0x1f),
		width & 0xff
	};

	v4l2_dbg(2, debug, sd, "%s\n", __func__);

	if (is_analog_input(sd)) {

		io_write(sd, 0x00, 0x07);
		io_write(sd, 0x01, 0x02);

		cp_write_clr_set(sd, 0x81, 0x10, 0x10);


		if (regmap_raw_write(state->regmap[ADV76XX_PAGE_IO],
					0x16, pll, 2))
			v4l2_err(sd, "writing to reg 0x16 and 0x17 failed\n");


		cp_write(sd, 0xa2, (cp_start_sav >> 4) & 0xff);
		cp_write(sd, 0xa3, ((cp_start_sav & 0x0f) << 4) |
				   ((cp_start_eav >> 8) & 0x0f));
		cp_write(sd, 0xa4, cp_start_eav & 0xff);


		cp_write(sd, 0xa5, (cp_start_vbi >> 4) & 0xff);
		cp_write(sd, 0xa6, ((cp_start_vbi & 0xf) << 4) |
				   ((cp_end_vbi >> 8) & 0xf));
		cp_write(sd, 0xa7, cp_end_vbi & 0xff);
	} else if (is_digital_input(sd)) {


		io_write(sd, 0x00, 0x02);
		io_write(sd, 0x01, 0x06);
	} else {
		v4l2_dbg(2, debug, sd, "%s: Unknown port %d selected\n",
				__func__, state->selected_input);
	}

	cp_write(sd, 0x8f, (ch1_fr_ll >> 8) & 0x7);
	cp_write(sd, 0x90, ch1_fr_ll & 0xff);
	cp_write(sd, 0xab, (height >> 4) & 0xff);
	cp_write(sd, 0xac, (height & 0x0f) << 4);
}
