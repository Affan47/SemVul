printer_dump(struct pr3o *p, Boolean is_err, Boolean is_dead)
{
	if (p->count) {


		if (p->buf[p->count - 1] == '\n')
			p->buf[--(p->count)] = '\0';
		else if (p->buf[p->count])
			p->buf[p->count] = '\0';


#if defined(X3270_DISPLAY)
		popup_printer_output(is_err, is_dead? NULL: printer_stop,
		    "%s", p->buf);
#else
		action_output("%s", p->buf);
#endif
		p->count = 0;
	}
}
