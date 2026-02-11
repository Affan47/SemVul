utf8_2uni(struct convert_rock *rock, int c)
{
    struct table_state *s = (struct table_state *)rock->state;


    if (c == 0xfffd) {
	convert_putc(rock->next, c);
	return;
    }

    if ((c & 0xf8) == 0xf0) {

	s->bytesleft = 3;
	s->codepoint = c & 0x07;
    }
    else if ((c & 0xf0) == 0xe0) {

	s->bytesleft = 2;
	s->codepoint = c & 0x0f;
    }
    else if ((c & 0xe0) == 0xc0) {

	s->bytesleft = 1;
	s->codepoint = c & 0x1f;
    }
    else if ((c & 0xc0) == 0x80) {

	if (s->bytesleft > 0) {
	    s->codepoint = (s->codepoint << 6) + (c & 0x3f);
	    s->bytesleft--;
	    if (!s->bytesleft) {
	        convert_putc(rock->next, s->codepoint);
		s->codepoint = 0;
	    }
	}
    }
    else {
	convert_putc(rock->next, c);
	s->bytesleft = 0;
	s->codepoint = 0;
    }
}
