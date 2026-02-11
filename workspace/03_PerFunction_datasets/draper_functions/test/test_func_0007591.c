gf_net_mobileip_set_callback(gf_net_mobileip_ctrl_cbk _mobip_cbk, const char *mip)
{
	mobip_cbk = _mobip_cbk;
	MobileIPAdd = _mobip_cbk ? mip : NULL;
}
