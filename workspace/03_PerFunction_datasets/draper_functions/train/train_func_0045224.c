ghc_list_add(struct ghc *ghc)
{
	g_return_if_fail(ghc);

	if (random_value(100) < 50) {
		list_append(ghc_list, ghc);
	} else {
		list_prepend(ghc_list, ghc);
	}
}
