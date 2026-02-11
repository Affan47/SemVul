wotpprin(const char *sofar, const int hf)
{
	FILE	*f;

	if  (hf  &&  (f = hexists(ptdir, (char *) 0)))
		return  makefvec(f);

	return  squeeze(mconcat(j_prins(sofar), listdir(ptdir, (char *) 0, isprin, sofar)));
}
