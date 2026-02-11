check_canonical_path(char **newval, void **extra, GucSource source)
{


	if (*newval)
		canonicalize_path(*newval);
	return true;
}
