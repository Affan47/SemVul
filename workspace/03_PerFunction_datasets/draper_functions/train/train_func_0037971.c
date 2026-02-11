splitcheck(int i)
{
	if (pgmflags[i] & PF_REF)
		pgmflags[i] |= PF_SPLIT;
}
