ad_define_option( const char *name, const char *fname, int lineno )
{
	int i;
	unsigned int optlen;

	if ( options == &lang_option ) {
		options = NULL;
		option_count = 0;
	}
	if ( name == NULL )
		return 0;

	optlen = 0;
	do {
		if ( !DESC_CHAR( name[optlen] ) ) {

			if ( name[optlen] == '=' && !name[optlen+1] ) {
				msad_range_hack = 1;
				continue;
			}
			Debug( LDAP_DEBUG_ANY,
			       "%s: line %d: illegal option name \"%s\"\n",
				    fname, lineno, name );
			return 1;
		}
	} while ( name[++optlen] );

	options = ch_realloc( options,
		(option_count+1) * sizeof(Attr_option) );

	if ( strcasecmp( name, "binary" ) == 0
	     || ad_find_option_definition( name, optlen ) ) {
		Debug( LDAP_DEBUG_ANY,
		       "%s: line %d: option \"%s\" is already defined\n",
		       fname, lineno, name );
		return 1;
	}

	for ( i = option_count; i; --i ) {
		if ( strcasecmp( name, options[i-1].name.bv_val ) >= 0 )
			break;
		options[i] = options[i-1];
	}

	options[i].name.bv_val = ch_strdup( name );
	options[i].name.bv_len = optlen;
	options[i].prefix = (name[optlen-1] == '-') ||
 		(name[optlen-1] == '=');

	if ( i != option_count &&
	     options[i].prefix &&
	     optlen < options[i+1].name.bv_len &&
	     strncasecmp( name, options[i+1].name.bv_val, optlen ) == 0 ) {
			Debug( LDAP_DEBUG_ANY,
			       "%s: line %d: option \"%s\" overrides previous option\n",
				    fname, lineno, name );
			return 1;
	}

	option_count++;
	return 0;
}
