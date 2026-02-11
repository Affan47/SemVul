try_get_next_char(uchar **in, int *c1) {
	*c1 = 0;
	if (**in != 0) {

		uchar code = chr_code[**in];
		if (code == 1 || code == 10) {
			*c1 = **in;
			(*in)++;
		}
	}
}
