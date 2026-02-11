sp887x_setup_agc (struct sp887x_state* state)
{

	dprintk("%s\n", __func__);
	sp887x_writereg(state, 0x33c, 0x054);
	sp887x_writereg(state, 0x33b, 0x04c);
	sp887x_writereg(state, 0x328, 0x000);
	sp887x_writereg(state, 0x327, 0x005);
	sp887x_writereg(state, 0x326, 0x001);
	sp887x_writereg(state, 0x325, 0x001);
	sp887x_writereg(state, 0x324, 0x001);
	sp887x_writereg(state, 0x318, 0x050);
	sp887x_writereg(state, 0x317, 0x3fe);
	sp887x_writereg(state, 0x316, 0x001);
	sp887x_writereg(state, 0x313, 0x005);
	sp887x_writereg(state, 0x312, 0x002);
	sp887x_writereg(state, 0x306, 0x000);
	sp887x_writereg(state, 0x303, 0x000);
}
