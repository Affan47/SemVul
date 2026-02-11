perl_xmmsclient_get_magic_from_sv (SV *sv, const char *class) {
	MAGIC *mg;

	if (!sv || !SvOK (sv) || !SvROK (sv)) {
		croak ("scalar isn't a reference");
	}

	if (!sv_derived_from (sv, class)) {
		croak ("object isn't a %s", class);
	}

	if (!(mg = mg_find (SvRV (sv), PERL_MAGIC_ext))) {
		croak ("failed to find c structure attached to scalar");
	}

	return mg;
}
