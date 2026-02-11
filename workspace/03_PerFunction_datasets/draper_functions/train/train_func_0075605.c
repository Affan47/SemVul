CFontzPacket_num(Driver *drvthis, int x, int num)
{
	PrivateData *p = drvthis->private_data;
	int do_init = 0;

	if ((num < 0) || (num > 10))
		return;

	if (p->ccmode != bignum) {
		if (p->ccmode != standard) {

			report(RPT_WARNING, "%s: num: cannot combine two modes using user-defined characters",
					drvthis->name);
			return;
		}

		p->ccmode = bignum;

		do_init = 1;
	}


	lib_adv_bignum(drvthis, x, num, 0, do_init);
}
