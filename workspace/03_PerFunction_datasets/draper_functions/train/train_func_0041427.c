find_box( const char *s )
{
	config_t *p;
	char *t;

	if (!memcmp( s, Home, HomeLen ) && s[HomeLen] == '/')
		s += HomeLen + 1;
	for (p = boxes; p; p = p->next) {
		if (!strcmp( s, p->path ) || (p->alias && !strcmp( s, p->alias )))
			return p;


		t = expand_strdup( p->path );
		if (!strcmp( s, t )) {
			free( t );
			return p;
		}
		free( t );
	}
	return 0;
}
