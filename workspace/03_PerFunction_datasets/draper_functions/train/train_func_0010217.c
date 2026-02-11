cob_accept (cob_field *f)
{


	cob_field_attr	attr;
	cob_field	temp;

	if (cob_screen_initialized) {
		cob_field_accept (f, NULL, NULL, NULL, NULL, NULL, 0);
		return;
	}
	temp.data = term_buff;
	temp.attr = &attr;
	COB_ATTR_INIT (COB_TYPE_ALPHANUMERIC, 0, 0, 0, NULL);

	if (fgets ((char *)term_buff, COB_MEDIUM_BUFF, stdin) == NULL) {
		temp.size = 1;
		term_buff[0] = ' ';
		term_buff[1] = 0;
	} else {
		temp.size = strlen ((char *)term_buff) - 1;
	}
	if (COB_FIELD_TYPE(f) == COB_TYPE_NUMERIC_DISPLAY) {
		if (temp.size > f->size) {
			temp.size = f->size;
		}
	}
	cob_move (&temp, f);


}
