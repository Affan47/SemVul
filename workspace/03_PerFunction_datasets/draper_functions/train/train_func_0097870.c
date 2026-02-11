map_print_key(EditLine *el, el_action_t *map, const Char *in)
{
	char outbuf[EL_BUFSIZ];
	el_bindings_t *bp, *ep;

	if (in[0] == '\0' || in[1] == '\0') {
		(void) keymacro__decode_str(in, outbuf, sizeof(outbuf), "");
		ep = &el->el_map.help[el->el_map.nfunc];
		for (bp = el->el_map.help; bp < ep; bp++)
			if (bp->func == map[(unsigned char) *in]) {
				(void) fprintf(el->el_outfile,
				    "%s\t->\t" FSTR "\n", outbuf, bp->name);
				return;
			}
	} else
		keymacro_print(el, in);
}
