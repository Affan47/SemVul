uloop_over(const int fid, void (*fn)(int, char *, int_ugid_t), char *arg)
{
	struct  uhash  *hp;
	unsigned	hi;

	if  (!doneit)
		rpwfile();
	for  (hi = 0;  hi < HASHMOD;  hi++)
		for  (hp = uhash[hi];  hp;  hp = hp->pwh_next)
			(*fn)(fid, arg, hp->pwh_uid);
}
