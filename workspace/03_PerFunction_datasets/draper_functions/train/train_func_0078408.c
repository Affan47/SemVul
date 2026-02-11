post_request()
{
    char *binddn = NULL;
    char *dorootbind = NULL;

    dsgw_send_header();


    dorootbind = dsgw_get_cgi_var( "authasrootdn", DSGW_CGIVAR_OPTIONAL );
    if ( dorootbind != NULL && !strcasecmp( dorootbind, "true" )) {
	binddn = dsgw_ch_strdup( gc->gc_rootdn );
    } else {
	binddn = dsgw_get_escaped_cgi_var( "escapedbinddn", "binddn",
	    DSGW_CGIVAR_OPTIONAL );
    }

    dsgw_emit_auth_form( binddn );
}
