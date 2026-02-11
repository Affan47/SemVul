netxen_cleanup_minidump(struct netxen_adapter *adapter)
{
	kfree(adapter->mdump.md_template);
	adapter->mdump.md_template = NULL;

	if (adapter->mdump.md_capture_buff) {
		vfree(adapter->mdump.md_capture_buff);
		adapter->mdump.md_capture_buff = NULL;
	}
}
