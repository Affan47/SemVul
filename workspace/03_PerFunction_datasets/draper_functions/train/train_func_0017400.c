do_differentiate (double *par)
{
	GMT_LONG	k;
	double scale, fact;


	scale = (*par != 0.0) ? *par : 1.0;
	datac[0] = datac[1] = 0.0;
	for (k = 2; k < ndatac; k+= 2) {
		fact = scale * modk(k);
		datac[k] *= (float)fact;
		datac[k+1] *= (float)fact;
	}
}
