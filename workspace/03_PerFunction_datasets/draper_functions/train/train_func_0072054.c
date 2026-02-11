au_cache_init(void)
{
	au_cachep[AuCache_DINFO] = AuCacheCtor(au_dinfo, au_di_init_once);
	if (au_cachep[AuCache_DINFO])

		au_cachep[AuCache_ICNTNR] = AuCacheCtor(au_icntnr,
							au_icntnr_init_once);
	if (au_cachep[AuCache_ICNTNR])
		au_cachep[AuCache_FINFO] = AuCacheCtor(au_finfo,
						       au_fi_init_once);
	if (au_cachep[AuCache_FINFO])
		au_cachep[AuCache_VDIR] = AuCache(au_vdir);
	if (au_cachep[AuCache_VDIR])
		au_cachep[AuCache_DEHSTR] = AuCache(au_vdir_dehstr);
	if (au_cachep[AuCache_DEHSTR])
		return 0;

	return -ENOMEM;
}
