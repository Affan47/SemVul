fullpath_alloc( struct berval *dest, const struct berval *dir, ber_len_t more )
{
	char *s = SLAP_MALLOC( dir->bv_len + more + 2 );

	dest->bv_val = s;
	if ( s == NULL ) {
		dest->bv_len = 0;
		Debug( LDAP_DEBUG_ANY, "back-ldif: out of memory\n", 0, 0, 0 );
	} else {
		s = lutil_strcopy( dest->bv_val, dir->bv_val );
		*s++ = LDAP_DIRSEP[0];
		*s = '\0';
		dest->bv_len = s - dest->bv_val;
	}
	return s;
}
