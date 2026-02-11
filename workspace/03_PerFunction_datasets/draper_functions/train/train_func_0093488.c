ssl_GetWrappingKey( PRInt32                   symWrapMechIndex,
                    SSL3KEAType               exchKeyType,
		    SSLWrappedSymWrappingKey *wswk)
{
    PRBool rv;

    PORT_Assert( (unsigned)exchKeyType < kt_kea_size);
    PORT_Assert( (unsigned)symWrapMechIndex < SSL_NUM_WRAP_MECHS);
    if ((unsigned)exchKeyType < kt_kea_size &&
        (unsigned)symWrapMechIndex < SSL_NUM_WRAP_MECHS) {
	rv = getSvrWrappingKey(symWrapMechIndex, exchKeyType, wswk,
	                       &globalCache, 0);
    } else {
    	rv = PR_FALSE;
    }

    return rv;
}
