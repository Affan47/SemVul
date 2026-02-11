invalid_range(eap)
    exarg_T	*eap;
{
    if (       eap->line1 < 0
	    || eap->line2 < 0
	    || eap->line1 > eap->line2
	    || ((eap->argt & RANGE)
		&& !(eap->argt & NOTADR)
		&& eap->line2 > curbuf->b_ml.ml_line_count
#ifdef FEAT_DIFF
			+ (eap->cmdidx == CMD_diffget)
#endif
		))
	return (char_u *)_(e_invrange);
    return NULL;
}
