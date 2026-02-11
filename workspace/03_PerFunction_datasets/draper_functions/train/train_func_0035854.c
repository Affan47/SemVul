do_otp_write(struct map_info *map, struct flchip *chip, loff_t adr,
			size_t len, u_char *buf, size_t grouplen)
{
	int ret;
	while (len) {
		unsigned long bus_ofs = adr & ~(map_bankwidth(map)-1);
		int gap = adr - bus_ofs;
		int n = min_t(int, len, map_bankwidth(map) - gap);
		map_word datum = map_word_ff(map);

		if (n != map_bankwidth(map)) {

			otp_enter(map, chip, bus_ofs, map_bankwidth(map));
			datum = map_read(map, bus_ofs);
			otp_exit(map, chip, bus_ofs, map_bankwidth(map));
		}

		datum = map_word_load_partial(map, datum, buf, gap, n);
		ret = do_write_oneword(map, chip, bus_ofs, datum, FL_OTP_WRITE);
		if (ret)
			return ret;

		adr += n;
		buf += n;
		len -= n;
	}

	return 0;
}
