encapinfo_init(encapinfo_t *pkginfo)
{
	memset(pkginfo, 0, sizeof(encapinfo_t));
	pkginfo->ei_rl_l = encap_list_new(LIST_USERFUNC, NULL);
	if (pkginfo->ei_rl_l == NULL)
		return -1;
	pkginfo->ei_ld_l = encap_list_new(LIST_USERFUNC, NULL);
	if (pkginfo->ei_ld_l == NULL)
		return -1;
	pkginfo->ei_ex_l = encap_list_new(LIST_USERFUNC, NULL);
	if (pkginfo->ei_ex_l == NULL)
		return -1;
	pkginfo->ei_pr_l = encap_list_new(LIST_USERFUNC, NULL);
	if (pkginfo->ei_pr_l == NULL)
		return -1;
	pkginfo->ei_ln_h = encap_hash_new(128, NULL);
	if (pkginfo->ei_ln_h == NULL)
		return -1;
	return 0;
}
