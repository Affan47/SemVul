khugepaged(void *none)
{
	struct mm_slot *mm_slot;

	set_freezable();
	set_user_nice(current, MAX_NICE);

	while (!kthread_should_stop()) {
		khugepaged_do_scan();
		khugepaged_wait_work();
	}

	spin_lock(&khugepaged_mm_lock);
	mm_slot = khugepaged_scan.mm_slot;
	khugepaged_scan.mm_slot = NULL;
	if (mm_slot)
		collect_mm_slot(mm_slot);
	spin_unlock(&khugepaged_mm_lock);
	return 0;
}
