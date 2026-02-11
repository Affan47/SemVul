init_addba_retry_timer23a(struct sta_info *psta)
{
	setup_timer(&psta->addba_retry_timer, addba_timer_hdl,
		    (unsigned long)psta);
}
