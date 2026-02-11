do_step (byte *msg, size_t msglen)
{
	int steps = msg[2] & 0x3f;

	if (msg[2] & 0x40) {
		steps = -steps;
	}

	Step (*this, steps);
	return 0;
}
