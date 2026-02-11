func_strchr(eval_scalar *r, eval_str *p1, eval_str *p2)
{
	if (p2->len) {
		if (p1->len) {
			char *pos = (char *)memchr(p1->value, *p2->value, p1->len);
			if (pos) {
				scalar_create_int_c(r, pos-p1->value);
			} else {
				scalar_create_int_c(r, -1);
			}
		} else {
			scalar_create_int_c(r, -1);
		}
		return 1;
	} else {
		return 0;
	}
}
