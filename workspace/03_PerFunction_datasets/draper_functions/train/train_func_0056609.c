slap_entry2mods(
	Entry *e,
	Modifications **mods,
	const char **text,
	char *textbuf, size_t textlen )
{
	Modifications	*modhead = NULL;
	Modifications	*mod;
	Modifications	**modtail = &modhead;
	Attribute		*a_new;
	AttributeDescription	*a_new_desc;
	int				i, count;

	a_new = e->e_attrs;

	while ( a_new != NULL ) {
		a_new_desc = a_new->a_desc;
		mod = (Modifications *) ch_malloc( sizeof( Modifications ));

		mod->sml_op = LDAP_MOD_REPLACE;
		mod->sml_flags = 0;

		mod->sml_type = a_new_desc->ad_cname;

		count = a_new->a_numvals;
		mod->sml_numvals = a_new->a_numvals;

		mod->sml_values = (struct berval*) ch_malloc(
			(count+1) * sizeof( struct berval) );


		if ( a_new->a_vals != a_new->a_nvals ) {
			mod->sml_nvalues = (struct berval*) ch_malloc(
				(count+1) * sizeof( struct berval) );
		} else {
			mod->sml_nvalues = NULL;
		}

		for ( i = 0; i < count; i++ ) {
			ber_dupbv(mod->sml_values+i, a_new->a_vals+i);
			if ( mod->sml_nvalues ) {
				ber_dupbv( mod->sml_nvalues+i, a_new->a_nvals+i );
			}
		}

		mod->sml_values[count].bv_val = NULL;
		mod->sml_values[count].bv_len = 0;

		if ( mod->sml_nvalues ) {
			mod->sml_nvalues[count].bv_val = NULL;
			mod->sml_nvalues[count].bv_len = 0;
		}

		mod->sml_desc = a_new_desc;
		mod->sml_next =NULL;
		*modtail = mod;
		modtail = &mod->sml_next;
		a_new = a_new->a_next;
	}

	*mods = modhead;

	return LDAP_SUCCESS;
}
