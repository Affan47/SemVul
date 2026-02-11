mode_type_flag(unsigned type, const struct termios *mode)
{
	static const uint8_t tcflag_offsets[] ALIGN1 = {
		offsetof(struct termios, c_cflag),
		offsetof(struct termios, c_iflag),
		offsetof(struct termios, c_oflag),
		offsetof(struct termios, c_lflag)
	};

	if (type <= local) {
		return (tcflag_t*) (((char*)mode) + tcflag_offsets[type]);
	}
	return NULL;
}
