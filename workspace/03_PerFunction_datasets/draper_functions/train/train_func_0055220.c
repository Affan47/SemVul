ghc_new(const char *url)
{
	struct ghc *ghc;

	g_assert(url != NULL);

	WALLOC0(ghc);
	ghc->url = atom_str_get(url);
	ghc->stamp = 0;
	ghc->used = 0;

	return ghc;
}
