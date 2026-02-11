cache_open(void)
{
	assoc[GTAGS]  = assoc_open('d');
	assoc[GRTAGS] = assoc_open('r');
	assoc[GSYMS] = symbol ? assoc_open('y') : NULL;
}
