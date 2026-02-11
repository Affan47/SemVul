try_lock(BW *bw,B *b)
{


	if (!nolocks && plain_file(b)) {
		unsigned char bf1[256];
		unsigned char bf[300];
		int x;

		if (lock_it(b->name,bf1)) {
			for(x=0;bf1[x] && bf1[x]!=':';++x);
			bf1[x]=0;
			if(bf1[0])
				joe_snprintf_1(bf,sizeof(bf),joe_gettext(LOCKMSG1),bf1);
			else
				joe_snprintf_0(bf,sizeof(bf),joe_gettext(LOCKMSG2));
			if (mkqw(bw->parent, sz(bf), steal_lock, NULL, b, NULL)) {
				uquery(bw);
				if (!b->locked)
					return 0;
			} else
				return 0;
		} else {

			b->locked = 1;
		}
	}
	return 1;
}
