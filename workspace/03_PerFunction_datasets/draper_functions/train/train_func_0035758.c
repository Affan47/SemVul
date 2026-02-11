userdb_mkmd5pw(const char *buf)
{
	int	i;
	char salt[9];

	salt[8]=0;
#ifdef	RANDOM
	userdb_get_random(salt, 8);
	for (i=0; i<8; i++)
		salt[i] = userdb_hex64[salt[i] & 63 ];

#else
	{

		struct {
#if HAVE_GETTIMEOFDAY
			struct timeval tv;
#else
			time_t	tv;
#endif
			pid_t	p;
		} s;

		MD5_DIGEST	d;
#if HAVE_GETTIMEOFDAY
		struct timezone tz;

		gettimeofday(&s.tv, &tz);
#else
		time(&s.tv);
#endif
		s.p=getpid();

		md5_digest(&s, sizeof(s), d);
		for (i=0; i<8; i++)
			salt[i]=userdb_hex64[ ((unsigned char *)d)[i] ];
	}
#endif
	return (md5_crypt(buf, salt));
}
