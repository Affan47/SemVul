mbm_cleanup(void)
{
	if (!mbm_enabled)
		return;

	kfree(mbm_local);
	kfree(mbm_total);
	mbm_enabled = false;
}
