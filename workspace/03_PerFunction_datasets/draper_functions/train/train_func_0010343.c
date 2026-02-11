do_show(int argc, char **argv)
{
	struct l2tp_data data;
	struct l2tp_parm *p = &data.config;

	if (parse_args(argc, argv, L2TP_GET, p) < 0)
		return -1;

	if (!p->tunnel && !p->session)
		missarg("tunnel or session");

	if (p->session)
		get_session(&data);
	else
		get_tunnel(&data);

	return 0;
}
