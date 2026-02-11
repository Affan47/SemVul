dsgw_getvp( int cginum )
{
    char	*cginame;
    char	*surl;

    int		i;

    if ( cginum < 1 || cginum > DSGW_MODE_NUMMODES ) {
	return "";
    }
    if ( vpmap == NULL ) {

	vpmap = dsgw_ch_malloc(( DSGW_MODE_NUMMODES + 1 ) * sizeof( char * ));
	for ( i = 0; i <= DSGW_MODE_NUMMODES; i++ ) {
	    vpmap[ i ] = NULL;
	}
    }

    if ( vpmap[ cginum ] == NULL ) {
	switch ( cginum ) {
	case DSGW_CGINUM_DOSEARCH:
	    cginame = DSGW_CGINAME_DOSEARCH;
	    break;
	case DSGW_CGINUM_BROWSE:
	    cginame = DSGW_CGINAME_BROWSE;
	    break;
	case DSGW_CGINUM_SEARCH:
	    cginame = DSGW_CGINAME_SEARCH;
	    break;
	case DSGW_CGINUM_CSEARCH:
	    cginame = DSGW_CGINAME_CSEARCH;
	    break;
	case DSGW_CGINUM_AUTH:
	    cginame = DSGW_CGINAME_AUTH;
	    break;
	case DSGW_CGINUM_EDIT:
	    cginame = DSGW_CGINAME_EDIT;
	    break;
	case DSGW_CGINUM_DOMODIFY:
	    cginame = DSGW_CGINAME_DOMODIFY;
	    break;
	case DSGW_CGINUM_DNEDIT:
	    cginame = DSGW_CGINAME_DNEDIT;
	    break;
	case DSGW_CGINUM_TUTOR:
	    cginame = DSGW_CGINAME_TUTOR;
	    break;
	case DSGW_CGINUM_LANG:
	    cginame = DSGW_CGINAME_LANG;
	    break;
	default:
	    return "";
	}

	if (( surl = dsgw_server_url() ) == NULL ) {
	  surl = "";
	}

	vpmap[ cginum ] = dsgw_ch_malloc( strlen( gc->gc_urlpfxcgi ) + strlen( surl )

					  + strlen( cginame ) + 3 );

	sprintf( vpmap[ cginum ], "%s%s/%s", surl,

		 gc->gc_urlpfxcgi, cginame );


    }
    return( vpmap[ cginum ]);
}
