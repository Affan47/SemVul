CAST_decrypt(CAST_LONG *data, const CAST_KEY *key)
	{
	register CAST_LONG l,r,t;
	const register CAST_LONG *k;

	k= &(key->data[0]);
	l=data[0];
	r=data[1];

	if(!key->short_key)
	    {
	    E_CAST(15,k,l,r,+,^,-);
	    E_CAST(14,k,r,l,-,+,^);
	    E_CAST(13,k,l,r,^,-,+);
	    E_CAST(12,k,r,l,+,^,-);
	    }
	E_CAST(11,k,l,r,-,+,^);
	E_CAST(10,k,r,l,^,-,+);
	E_CAST( 9,k,l,r,+,^,-);
	E_CAST( 8,k,r,l,-,+,^);
	E_CAST( 7,k,l,r,^,-,+);
	E_CAST( 6,k,r,l,+,^,-);
	E_CAST( 5,k,l,r,-,+,^);
	E_CAST( 4,k,r,l,^,-,+);
	E_CAST( 3,k,l,r,+,^,-);
	E_CAST( 2,k,r,l,-,+,^);
	E_CAST( 1,k,l,r,^,-,+);
	E_CAST( 0,k,r,l,+,^,-);

	data[1]=l&0xffffffffL;
	data[0]=r&0xffffffffL;
	}
