socket_mt_save(const void *ip, const struct xt_entry_match *match)
{
	const struct xt_socket_mtinfo1 *info = (const void *)match->data;

	if (info->flags & XT_SOCKET_TRANSPARENT)
		printf(" --transparent");
}
