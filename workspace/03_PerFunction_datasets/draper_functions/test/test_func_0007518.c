ixgbevf_save_reset_stats(struct ixgbevf_adapter *adapter)
{

	if (adapter->stats.vfgprc || adapter->stats.vfgptc) {
		adapter->stats.saved_reset_vfgprc += adapter->stats.vfgprc -
			adapter->stats.base_vfgprc;
		adapter->stats.saved_reset_vfgptc += adapter->stats.vfgptc -
			adapter->stats.base_vfgptc;
		adapter->stats.saved_reset_vfgorc += adapter->stats.vfgorc -
			adapter->stats.base_vfgorc;
		adapter->stats.saved_reset_vfgotc += adapter->stats.vfgotc -
			adapter->stats.base_vfgotc;
		adapter->stats.saved_reset_vfmprc += adapter->stats.vfmprc -
			adapter->stats.base_vfmprc;
	}
}
