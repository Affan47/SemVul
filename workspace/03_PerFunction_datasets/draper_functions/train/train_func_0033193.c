nf_getparameter(int i)
{
	if (i < 0)
		return 0;

	return ReadInt32(context + i*4);
}
