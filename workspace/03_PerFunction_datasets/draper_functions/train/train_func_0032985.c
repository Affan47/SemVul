setup_switch(int frontend_fd, adapter *ad, transponder *tp)
{
	int hiband = 0;
	int diseqc = (tp->diseqc > 0) ? tp->diseqc - 1 : 0;
	int freq = tp->freq;
	int pol = (tp->pol - 1) & 1;

	if (tp->pol > 2)
	{
		freq = (freq - LOF3);
		hiband = 0;
	}
	else if (freq < SLOF)
	{
		freq = (freq - LOF1);
		hiband = 0;
	}
	else
	{
		freq = (freq - LOF2);
		hiband = 1;
	}

	if (tp->diseqc_param.switch_type == SWITCH_UNICABLE)
	{
		freq = send_unicable(frontend_fd, freq / 1000, diseqc, pol, hiband,
				&tp->diseqc_param);
	}
	else if (tp->diseqc_param.switch_type == SWITCH_JESS)
	{
		freq = send_jess(frontend_fd, freq / 1000, diseqc, pol, hiband,
				&tp->diseqc_param);
	}
	else if (tp->diseqc_param.switch_type == SWITCH_SLAVE)
	{
		LOGL(2, "FD %d is a slave adapter", frontend_fd);
	}
	else
	{
		if (ad->old_pol != pol || ad->old_hiband != hiband
				|| ad->old_diseqc != diseqc)
			send_diseqc(frontend_fd, diseqc, ad->old_diseqc != diseqc, pol,
					hiband, &tp->diseqc_param);
		else
			LOGL(3, "Skip sending diseqc commands since "
					"the switch position doesn't need to be changed: "
					"pol %d, hiband %d, switch position %d", pol, hiband,
					diseqc);
	}

	ad->old_pol = pol;
	ad->old_hiband = hiband;
	ad->old_diseqc = diseqc;

	return freq;
}
