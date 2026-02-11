string_print(char *str, int id, snd_output_t *out)
{
	unsigned char *p = (unsigned char *)str;
	if (!p || !*p) {
		snd_output_puts(out, "''");
		return;
	}
	if (!id) {
		switch (*p) {
		case '0' ... '9':
		case '-':
			goto quoted;
		}
	}
 loop:
	switch (*p) {
	case 0:
		goto nonquoted;
	case 1 ... 31:
	case 127 ... 255:
	case ' ':
	case '=':
	case ';':
	case ',':
	case '.':
	case '{':
	case '}':
	case '\'':
	case '"':
		goto quoted;
	default:
		p++;
		goto loop;
	}
 nonquoted:
	snd_output_puts(out, str);
	return;
 quoted:
	snd_output_putc(out, '\'');
	p = (unsigned char *)str;
	while (*p) {
		int c;
		c = *p;
		switch (c) {
		case '\n':
			snd_output_putc(out, '\\');
			snd_output_putc(out, 'n');
			break;
		case '\t':
			snd_output_putc(out, '\\');
			snd_output_putc(out, 't');
			break;
		case '\v':
			snd_output_putc(out, '\\');
			snd_output_putc(out, 'v');
			break;
		case '\b':
			snd_output_putc(out, '\\');
			snd_output_putc(out, 'b');
			break;
		case '\r':
			snd_output_putc(out, '\\');
			snd_output_putc(out, 'r');
			break;
		case '\f':
			snd_output_putc(out, '\\');
			snd_output_putc(out, 'f');
			break;
		case '\'':
			snd_output_putc(out, '\\');
			snd_output_putc(out, c);
			break;
		case 32 ... '\'' - 1:
		case '\'' + 1 ... 126:
			snd_output_putc(out, c);
			break;
		default:
			snd_output_printf(out, "\\%04o", c);
			break;
		}
		p++;
	}
	snd_output_putc(out, '\'');
}
