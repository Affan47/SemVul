princ_string(snd_output_t *out, char *s)
{
	char *p;

	snd_output_putc(out, '"');
	for (p = s; *p != '\0'; ++p)
		switch (*p) {
		case '\a': snd_output_putc(out, '\\'); snd_output_putc(out, 'a'); break;
		case '\b': snd_output_putc(out, '\\'); snd_output_putc(out, 'b'); break;
		case '\f': snd_output_putc(out, '\\'); snd_output_putc(out, 'f'); break;
		case '\n': snd_output_putc(out, '\\'); snd_output_putc(out, 'n'); break;
		case '\r': snd_output_putc(out, '\\'); snd_output_putc(out, 'r'); break;
		case '\t': snd_output_putc(out, '\\'); snd_output_putc(out, 't'); break;
		case '\v': snd_output_putc(out, '\\'); snd_output_putc(out, 'v'); break;
		case '"': snd_output_putc(out, '\\'); snd_output_putc(out, '"'); break;
		default: snd_output_putc(out, *p);
		}
	snd_output_putc(out, '"');
}
