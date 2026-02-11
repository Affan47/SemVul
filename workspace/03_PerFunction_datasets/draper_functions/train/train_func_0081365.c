scale( int new, lutil_int_decnum *prev, unsigned char *tmp )
{
	int i, j;
	unsigned char *in = prev->buf+prev->beg;
	unsigned int part;
	unsigned char *out = tmp + prev->bufsiz - prev->len;

	memset( tmp, 0, prev->bufsiz );
	if ( prev->len ) {
		for ( i = prev->len-1; i>=0; i-- ) {
			part = in[i] * FACTOR1;
			for ( j = i; part; j-- ) {
				part += out[j];
				out[j] = part & 0xff;
				part >>= 8;
			}
			part = in[i] * FACTOR2;
			for ( j = i-2; part; j-- ) {
				part += out[j];
				out[j] = part & 0xff;
				part >>= 8;
			}
		}
		j++;
		prev->beg += j;
		prev->len -= j;
	}

	out = tmp + prev->bufsiz;
	i = 0;
	do {
		i--;
		new += out[i];
		out[i] = new & 0xff;
		new >>= 8;
	} while ( new );
	i = -i;
	if ( prev->len < i ) {
		prev->beg = prev->bufsiz - i;
		prev->len = i;
	}
	AC_MEMCPY( prev->buf+prev->beg, tmp+prev->beg, prev->len );
}
