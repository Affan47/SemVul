addlenstr( lenstr *l, const char *str )
{
    size_t len;

    if ( NULL == l || NULL == str ) return;

    len = strlen( str );

    if ( l->ls_buf == NULL ) {

	l->ls_maxlen = ( len > LS_INCRSIZE ) ? len : LS_INCRSIZE;
	l->ls_len = len;
	l->ls_buf = slapi_ch_malloc( l->ls_maxlen + 1 );
	memcpy( l->ls_buf, str, len + 1 );
    } else {
	if ( l->ls_len + len > l->ls_maxlen ) {
	    l->ls_maxlen *= 2;
	    if (l->ls_maxlen < l->ls_len + len) {
		l->ls_maxlen += len;
	    }
	    l->ls_buf = slapi_ch_realloc( l->ls_buf, l->ls_maxlen + 1 );
	}
	memcpy( l->ls_buf + l->ls_len, str, len + 1 );
	l->ls_len += len;
    }
}
