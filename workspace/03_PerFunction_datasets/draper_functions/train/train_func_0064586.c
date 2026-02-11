cx18_av_initialize(struct v4l2_subdev *sd)
{
	struct cx18_av_state *state = to_cx18_av_state(sd);
	struct cx18 *cx = v4l2_get_subdevdata(sd);
	int default_volume;
	u32 v;

	cx18_av_loadfw(cx);

	cx18_av_write4_expect(cx, CXADEC_DL_CTL, 0x03000000,
						 0x03000000, 0x13000000);


	v = cx18_av_read4(cx, CXADEC_HOST_REG1);

	cx18_av_write4_expect(cx, CXADEC_HOST_REG1, v | 1, v, 0xfffe);

	cx18_av_write4_expect(cx, CXADEC_HOST_REG1, v & 0xfffe,
						    v & 0xfffe, 0xffff);


	v = cx18_av_read4(cx, CXADEC_DLL1_DIAG_CTRL) & 0xE1FFFEFF;

	cx18_av_write4(cx, CXADEC_DLL1_DIAG_CTRL, v);

	cx18_av_write4(cx, CXADEC_DLL1_DIAG_CTRL, v | 0x10000100);

	v = cx18_av_read4(cx, CXADEC_DLL2_DIAG_CTRL) & 0xE1FFFEFF;

	cx18_av_write4(cx, CXADEC_DLL2_DIAG_CTRL, v);

	cx18_av_write4(cx, CXADEC_DLL2_DIAG_CTRL, v | 0x06000100);


	cx18_av_write4(cx, CXADEC_AFE_DIAG_CTRL1, 0x000A1802);

	v = cx18_av_read4(cx, CXADEC_AFE_DIAG_CTRL3) | 1;

	cx18_av_write4_expect(cx, CXADEC_AFE_DIAG_CTRL3, v, v, 0x03009F0F);

	cx18_av_write4_expect(cx, CXADEC_AFE_DIAG_CTRL3,
			      v & 0xFFFFFFFE, v & 0xFFFFFFFE, 0x03009F0F);


	cx18_av_and_or4(cx, CXADEC_PIN_CTRL1, ~0, 0x040C00);


	cx18_av_and_or4(cx, CXADEC_PIN_CTRL2, ~0, 0x2);


	cx18_av_write4(cx, CXADEC_SOFT_RST_CTRL, 0x8000);
	cx18_av_write4(cx, CXADEC_SOFT_RST_CTRL, 0);


	cx18_av_and_or4(cx, CXADEC_CHIP_CTRL, 0xFFFBFFFF, 0x00120000);


	cx18_av_init(cx);


	cx18_av_and_or4(cx, CXADEC_MODE_CTRL, 0xFFF7E7F0, 0x02040800);


	cx18_av_and_or4(cx, CXADEC_CRUSH_CTRL, ~0, 0x00500000);


	cx18_av_and_or4(cx, CXADEC_DFE_CTRL2, 0xFFFF00FF, 0x00002000);


	cx18_av_write4(cx, CXADEC_OUT_CTRL1, 0x4013252e);


	cx18_av_and_or4(cx, CXADEC_AFE_CTRL, 0xFF000000, 0x00005D00);


	cx18_av_write4(cx, CXADEC_SRC_COMB_CFG, 0x6628021F);
	default_volume = cx18_av_read(cx, 0x8d4);


	if (default_volume > 228) {

		default_volume = 228;
		cx18_av_write(cx, 0x8d4, 228);
	} else if (default_volume < 20) {

		default_volume = 20;
		cx18_av_write(cx, 0x8d4, 20);
	}
	default_volume = (((228 - default_volume) >> 1) + 23) << 9;
	state->volume->cur.val = state->volume->default_value = default_volume;
	v4l2_ctrl_handler_setup(&state->hdl);
}
