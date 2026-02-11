be_calculate_vf_qs(struct be_adapter *adapter, u16 num_vfs)
{
	struct be_resources res = adapter->pool_res;
	u16 num_vf_qs = 1;


	if (num_vfs && !be_is_mc(adapter)) {


		if (num_vfs < (be_max_vfs(adapter) - 8))
			num_vf_qs = (res.max_rss_qs - 8) / num_vfs;
		else
			num_vf_qs = res.max_rss_qs / num_vfs;


		if (num_vfs >= MAX_RSS_IFACES)
			num_vf_qs = 1;
	}
	return num_vf_qs;
}
