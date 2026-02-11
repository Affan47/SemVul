khugepaged_wait_event(void)
{
	return !list_empty(&khugepaged_scan.mm_head) ||
		kthread_should_stop();
}
