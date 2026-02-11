textIterate(text *t_text, void (*cb)(const line_t *item, void *arg), void *arg, int destroy)
{


#if	0
	while(t_text) {
		(*cb)(t_text->t_line, arg);

		if(destroy && t_text->t_line) {
			lineUnlink(t_text->t_line);
			t_text->t_line = NULL;
		}

		t_text = t_text->t_next;
	}
#else
	if(destroy)
		while(t_text) {
			(*cb)(t_text->t_line, arg);

			if(t_text->t_line) {
				lineUnlink(t_text->t_line);
				t_text->t_line = NULL;
			}

			t_text = t_text->t_next;
		}
	else
		while(t_text) {
			(*cb)(t_text->t_line, arg);

			t_text = t_text->t_next;
		}
#endif
	return arg;
}
