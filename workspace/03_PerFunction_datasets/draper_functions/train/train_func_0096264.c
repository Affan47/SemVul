stv0299_set_FEC(struct stv0299_state *state, enum fe_code_rate fec)
{
	dprintk ("%s\n", __func__);

	switch (fec) {
	case FEC_AUTO:
	{
		return stv0299_writeregI (state, 0x31, 0x1f);
	}
	case FEC_1_2:
	{
		return stv0299_writeregI (state, 0x31, 0x01);
	}
	case FEC_2_3:
	{
		return stv0299_writeregI (state, 0x31, 0x02);
	}
	case FEC_3_4:
	{
		return stv0299_writeregI (state, 0x31, 0x04);
	}
	case FEC_5_6:
	{
		return stv0299_writeregI (state, 0x31, 0x08);
	}
	case FEC_7_8:
	{
		return stv0299_writeregI (state, 0x31, 0x10);
	}
	default:
	{
		return -EINVAL;
	}
    }
}
