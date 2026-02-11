il_setup_scan_deferred_work(struct il_priv *il)
{
	INIT_WORK(&il->scan_completed, il_bg_scan_completed);
	INIT_WORK(&il->abort_scan, il_bg_abort_scan);
	INIT_DELAYED_WORK(&il->scan_check, il_bg_scan_check);
}
