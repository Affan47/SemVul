prism2_info_scanresults(local_info_t *local, unsigned char *buf,
				    int left)
{
	u16 *pos;
	int new_count, i;
	unsigned long flags;
	struct hfa384x_scan_result *res;
	struct hfa384x_hostscan_result *results, *prev;

	if (left < 4) {
		printk(KERN_DEBUG "%s: invalid scanresult info frame "
		       "length %d\n", local->dev->name, left);
		return;
	}

	pos = (u16 *) buf;
	pos++;
	pos++;
	left -= 4;

	new_count = left / sizeof(struct hfa384x_scan_result);
	results = kmalloc(new_count * sizeof(struct hfa384x_hostscan_result),
			  GFP_ATOMIC);
	if (results == NULL)
		return;


	res = (struct hfa384x_scan_result *) pos;
	for (i = 0; i < new_count; i++) {
		memcpy(&results[i], &res[i],
		       sizeof(struct hfa384x_scan_result));
		results[i].atim = 0;
	}

	spin_lock_irqsave(&local->lock, flags);
	local->last_scan_type = PRISM2_SCAN;
	prev = local->last_scan_results;
	local->last_scan_results = results;
	local->last_scan_results_count = new_count;
	spin_unlock_irqrestore(&local->lock, flags);
	kfree(prev);

	hostap_report_scan_complete(local);


	set_bit(PRISM2_INFO_PENDING_SCANRESULTS, &local->pending_info);
	schedule_work(&local->info_queue);
}
