WriteFloat16( float inOutFloat, float floatMin, float floatMax )
{
	RakAssert(floatMax>floatMin);
	if (inOutFloat>floatMax+.001)
	{
		RakAssert(inOutFloat<=floatMax+.001);
	}
	if (inOutFloat<floatMin-.001)
	{
		RakAssert(inOutFloat>=floatMin-.001);
	}
	float percentile=65535.0f * (inOutFloat-floatMin)/(floatMax-floatMin);
	if (percentile<0.0)
		percentile=0.0;
	if (percentile>65535.0f)
		percentile=65535.0f;
	Write((unsigned short)percentile);
}
