__zadd__(zp1,zp2,out,len)
complex	*zp1, *zp2, *out;
int	len;
{
    int		i;
    for ( i = 0; i < len; i++ )
    {
	out[i].re = zp1[i].re + zp2[i].re;
	out[i].im = zp1[i].im + zp2[i].im;
    }
}
