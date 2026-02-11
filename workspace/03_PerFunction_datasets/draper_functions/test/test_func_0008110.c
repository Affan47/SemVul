do_kmap(Boolean on)
{
	status_add(KMAP, on ? (*standard_font ? 'K' : CG_K) : nullblank, KT_STD);
}
