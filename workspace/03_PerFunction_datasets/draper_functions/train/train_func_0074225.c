rtnl_rtscope_initialize(void)
{
	if (rtnl_rtscope_tab)
		return;
	rtnl_rtscope_tab = xzalloc(sizeof(*rtnl_rtscope_tab));
	rtnl_rtscope_tab->tab[0] = "global";
	rtnl_rtscope_tab->tab[255] = "nowhere";
	rtnl_rtscope_tab->tab[254] = "host";
	rtnl_rtscope_tab->tab[253] = "link";
	rtnl_rtscope_tab->tab[200] = "site";
	rtnl_tab_initialize("/etc/iproute2/rt_scopes", rtnl_rtscope_tab->tab);
}
