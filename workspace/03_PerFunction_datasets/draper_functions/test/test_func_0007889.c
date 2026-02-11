unparse_scatter(Stream * str, Scatter * sc)
{
    while (sc) {
	switch (sc->kind) {
	case SCAT_REST:
	    stream_add_char(str, '@');

	case SCAT_REQUIRED:
	    stream_add_string(str, prog->var_names[sc->id]);
	    break;
	case SCAT_OPTIONAL:
	    stream_printf(str, "?%s", prog->var_names[sc->id]);
	    if (sc->expr) {
		stream_add_string(str, " = ");
		unparse_expr(str, sc->expr);
	    }
	}
	if (sc->next)
	    stream_add_string(str, ", ");
	sc = sc->next;
    }
}
