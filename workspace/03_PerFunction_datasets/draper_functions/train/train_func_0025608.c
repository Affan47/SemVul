friends_init ()
{

	char *key, buf2[20];
	int f;
	long int r;
	time_t ti, tii;
	char t_friendsidstring[31];
	r = 0x12345678;
	f = open ("/dev/random", O_RDONLY);
	if (f >= 0)
	{
		read (f, &r, 4);
		close (f);
	}
	tii = ti = time (NULL);
	ti = ti & 0xffffff;
	r += ti;

	g_snprintf (buf2, sizeof (buf2), "$1$%08lx$", r);
	key = "havenocrypt";
#ifdef HAVE_CRYPT_H
	key = crypt ("servr", buf2);
	g_strlcpy (t_friendsidstring, (key + 12), sizeof (t_friendsidstring));
#else
	r = r * r;
	g_snprintf (t_friendsidstring, sizeof (t_friendsidstring),
		    "nocrypt%015ld", labs (r));
#endif
	printf ("\nKey: %s,id: %s %Zu bytes, time: %ld\n", key,
		t_friendsidstring, strlen (t_friendsidstring), ti);

	g_strlcpy (serverid, t_friendsidstring, sizeof (serverid));
	return (0);
}
