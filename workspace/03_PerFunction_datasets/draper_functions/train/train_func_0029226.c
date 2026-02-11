compare_tunning_parameters(int aid, transponder * tp)
{
	int same = 0;
	adapter *ad = get_adapter(aid);
	if (!ad)
                return -1;

	LOGL(4, "new parameters: f:%d, plp:%d, diseqc:%d, pol:%d, sr:%d, mtype:%d",
		tp->freq, tp->plp, tp->diseqc, tp->pol, tp->sr, tp->mtype);
	LOGL(4, "old parameters: f:%d, plp:%d, diseqc:%d, pol:%d, sr:%d, mtype:%d",
		ad->tp.freq, ad->tp.plp, ad->tp.diseqc, ad->tp.pol, ad->tp.sr, ad->tp.mtype);
	if (tp->freq != ad->tp.freq || tp->plp != ad->tp.plp
			|| tp->diseqc != ad->tp.diseqc
			|| (tp->pol > 0 && tp->pol != ad->tp.pol)
			|| (tp->sr > 1000 && tp->sr != ad->tp.sr)
			|| (tp->mtype > 0 && tp->mtype != ad->tp.mtype))

		return 1;

	return 0;
}
