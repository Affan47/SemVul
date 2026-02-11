ldapu_ber_free( LDAP* ld, BerElement *ber, int freebuf )
{
    if (ldapu_VTable.ldapuV_ber_free) {
	ldapu_VTable.ldapuV_ber_free (ld, ber, freebuf);
    }
}
