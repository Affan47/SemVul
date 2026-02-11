ldap_tmplattrs( struct ldap_disptmpl *tmpl, char **includeattrs,
	int exclude, unsigned long syntaxmask )
{


    struct ldap_tmplitem	*tirowp, *ticolp;
    int			i, attrcnt, memerr;
    char		**attrs;

    attrcnt = 0;
    memerr = 0;

    if (( attrs = (char **)dsgw_ch_malloc( sizeof( char * ))) == NULL ) {
	return( NULL );
    }

    if ( includeattrs != NULL ) {
	for ( i = 0; !memerr && includeattrs[ i ] != NULL; ++i ) {
	    if (( attrs = (char **)dsgw_ch_realloc( attrs, ( attrcnt + 2 ) *
		    sizeof( char * ))) == NULL || ( attrs[ attrcnt++ ] =
		    dsgw_ch_strdup( includeattrs[ i ] )) == NULL ) {
		memerr = 1;
	    } else {
		attrs[ attrcnt ] = NULL;
	    }
	}
    }

    for ( tirowp = ldap_first_tmplrow( tmpl );
	    !memerr && tirowp != NULLTMPLITEM;
	    tirowp = ldap_next_tmplrow( tmpl, tirowp )) {
	for ( ticolp = ldap_first_tmplcol( tmpl, tirowp );
		ticolp != NULLTMPLITEM;
		ticolp = ldap_next_tmplcol( tmpl, tirowp, ticolp )) {

	    if ( syntaxmask != 0 ) {
		if (( exclude &&
			( syntaxmask & ticolp->ti_syntaxid ) != 0 ) ||
			( !exclude &&
			( syntaxmask & ticolp->ti_syntaxid ) == 0 )) {
		    continue;
		}
	    }

	    if ( ticolp->ti_attrname != NULL ) {
		if (( attrs = (char **)dsgw_ch_realloc( attrs, ( attrcnt + 2 )
			* sizeof( char * ))) == NULL || ( attrs[ attrcnt++ ] =
			dsgw_ch_strdup( ticolp->ti_attrname )) == NULL ) {
		    memerr = 1;
		} else {
		    attrs[ attrcnt ] = NULL;
		}
	    }
	}
    }

    if ( memerr || attrcnt == 0 ) {
	for ( i = 0; i < attrcnt; ++i ) {
	    if ( attrs[ i ] != NULL ) {
		free( attrs[ i ] );
	    }
	}

	free( (char *)attrs );
	return( NULL );
    }

    return( attrs );
}
