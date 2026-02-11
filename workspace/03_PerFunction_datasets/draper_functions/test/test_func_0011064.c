gsm_L_asr P2((a,n), longword a, int n)
{
	if (n >= 32) return -(a < 0);
	if (n <= -32) return 0;
	if (n < 0) return a << -n;

#	ifdef	SASR
		return a >> n;
#	else
		if (a >= 0) return a >> n;
		else return -(longword)( -(ulongword)a >> n );
#	endif
}
