tee_tg_save(const void *ip, const struct xt_entry_target *target)
{
	const struct xt_tee_tginfo *info = (const void *)target->data;

	printf(" --gateway %s", xtables_ipaddr_to_numeric(&info->gw.in));
	if (*info->oif != '\0')
		printf(" --oif %s", info->oif);
}
