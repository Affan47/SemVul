jcnf_update(jcnf *p) {
	jc_error ev;
	struct stat sbuf;

	if (p->modified) {
		if (p->modify == 0 || p->locked == 0) {

			return jc_update_nomod;
		}
		if ((ev = jcnf_write(p)) != jc_ok) {
			return ev;
		}
		p->modified = 0;
	}
	p->modify = 0;

	return jc_ok;
}
