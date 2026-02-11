ReadGP(int w)
{
	uint8 ret;

	if(joy_readbit[w]>=8)
		ret = ((joy[2+w]>>(joy_readbit[w]&7))&1);
	else
		ret = ((joy[w]>>(joy_readbit[w]))&1);
	if(joy_readbit[w]>=16) ret=0;
	if(!FSAttached)
	{
		if(joy_readbit[w]>=8) ret|=1;
	}
	else
	{
		if(joy_readbit[w]==19-w) ret|=1;
	}
	if(!fceuindbg)
		joy_readbit[w]++;
	return ret;
}
