dsgw_delcookie( char *cookie )
{
    FILE *fp;
    char *rndstr, *dn, *dnp, *dbdn, *p;
    char buf[ CKBUFSIZ ];
    int rc;
    long buflen;


    if (( rndstr = strchr( cookie, '=' )) == NULL ) {

	return -1;
    } else {

	rndstr++;
	if (( dn = strchr( rndstr, ':' )) == NULL ) {

	    return -1;
	} else {
	    *dn++ = '\0';
	    dsgw_form_unescape( dn );
	}
    }


    if (( fp = dsgw_opencookiedb()) == NULL ) {
        return -1;
    }
    fgets( buf, sizeof(buf), fp );
    if ( strncmp( buf, "lastpurge:", 10 )) {
	dsgw_closecookiedb( fp );
	return -1;
    }
    rc = DSGW_CKDB_KEY_NOT_PRESENT;
    for (;;) {
	if ( fgets( buf, sizeof(buf), fp ) == NULL ) {
	    break;
	}
	if ( strncmp( buf, rndstr, CKLEN )) {
	    continue;
	}
	buflen = strlen( buf );

	if (( dbdn = strrchr( buf, ':' )) == NULL ) {
	    continue;
	} else {
	    dbdn++;
	    if ( dbdn[ strlen( dbdn) - 1 ] == '\n' ) {
		dbdn[ strlen( dbdn) - 1 ] = '\0';
	    }
	    if ( strcmp( dbdn, dn )) {
		continue;
	    } else {


		p = strchr( buf, ':' );
		for ( p++; *p != ':'; p++ ) {
		    *p = '0';
		}
		dnp = strrchr( buf, ':' );
		for ( p++; p < dnp; p++ ) {
		    *p = 'x';
		}
		p++;
		fseek( fp, -buflen, SEEK_CUR );
		fputs( buf, fp );
		fputs( "\n", fp );
		fflush( fp );
		rc = 0;
	    }
	}
    }

    dsgw_closecookiedb( fp );

    if ( rc == 0 ) {
	dsgw_purgedatabase( dn );
    }

    return rc;
}
