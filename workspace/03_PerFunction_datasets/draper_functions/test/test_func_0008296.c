int2cpt(int val)
{
	if (val >= 0) {

		if (val > 127)
			val = 127;

		return (unsigned char) val;

	} else {

		val = -val;

		if (val > 127)
			val = 127;

		return (unsigned char) (0x80 | val);
	}
}
