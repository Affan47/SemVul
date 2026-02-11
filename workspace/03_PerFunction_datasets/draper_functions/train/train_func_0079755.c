cob_str_from_fld (const cob_field *f)
{
	void		*mptr;
	unsigned char	*s;
	int		i;
	int		n;
	int		quote_switch;

	if (!f) {
		return cob_malloc (1);
	}
	for (i = (int) f->size - 1; i >= 0; i--) {
		if (f->data[i] != ' ' && f->data[i] != 0) {
			break;
		}
	}
	i++;

	mptr = cob_malloc ((size_t)(i + 1));
	quote_switch = 0;
	s = mptr;
	for (n = 0; n < i; n++) {
		if (f->data[n] == '"') {
			quote_switch = !quote_switch;
			continue;
		}
		s[n] = f->data[n];
		if (quote_switch) {
			continue;
		}
		if (s[n] == ' ' || s[n] == 0) {
			s[n] = 0;
			break;
		}

	}
	return mptr;
}
