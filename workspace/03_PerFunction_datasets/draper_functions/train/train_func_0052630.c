ntom_ins2outs(mpg123_handle *fr, off_t ins)
{
	off_t soff = 0;
	off_t ntm = ntom_val(fr,0);
#ifdef SAFE_NTOM
	{
		off_t block = spf(fr);
		if(ins <= 0) return 0;
		do
		{
			off_t nowblock = ins > block ? block : ins;
			ntm  += nowblock*fr->ntom_step;
			soff += ntm/NTOM_MUL;
			ntm  -= (ntm/NTOM_MUL)*NTOM_MUL;
			ins -= nowblock;
		} while(ins > 0);
	}
#else


	soff = ((off_t)ntm + (off_t)ins*(off_t)fr->ntom_step)/(off_t)NTOM_MUL;
#endif
	return soff;
}
