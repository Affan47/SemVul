raid6_dual_recov(int disks, size_t bytes, int faila, int failb, struct page **ptrs)
{
	struct async_submit_ctl submit;
	struct completion cmp;
	struct dma_async_tx_descriptor *tx = NULL;
	enum sum_check_flags result = ~0;

	if (faila > failb)
		swap(faila, failb);

	if (failb == disks-1) {
		if (faila == disks-2) {

			init_async_submit(&submit, 0, NULL, NULL, NULL, addr_conv);
			tx = async_gen_syndrome(ptrs, 0, disks, bytes, &submit);
		} else {
			struct page *blocks[disks];
			struct page *dest;
			int count = 0;
			int i;


			for (i = disks; i-- ; ) {
				if (i == faila || i == failb)
					continue;
				blocks[count++] = ptrs[i];
			}
			dest = ptrs[faila];
			init_async_submit(&submit, ASYNC_TX_XOR_ZERO_DST, NULL,
					  NULL, NULL, addr_conv);
			tx = async_xor(dest, blocks, 0, count, bytes, &submit);

			init_async_submit(&submit, 0, tx, NULL, NULL, addr_conv);
			tx = async_gen_syndrome(ptrs, 0, disks, bytes, &submit);
		}
	} else {
		if (failb == disks-2) {

			init_async_submit(&submit, 0, NULL, NULL, NULL, addr_conv);
			tx = async_raid6_datap_recov(disks, bytes, faila, ptrs, &submit);
		} else {

			init_async_submit(&submit, 0, NULL, NULL, NULL, addr_conv);
			tx = async_raid6_2data_recov(disks, bytes, faila, failb, ptrs, &submit);
		}
	}
	init_completion(&cmp);
	init_async_submit(&submit, ASYNC_TX_ACK, tx, callback, &cmp, addr_conv);
	tx = async_syndrome_val(ptrs, 0, disks, bytes, &result, spare, &submit);
	async_tx_issue_pending(tx);

	if (wait_for_completion_timeout(&cmp, msecs_to_jiffies(3000)) == 0)
		pr("%s: timeout! (faila: %d failb: %d disks: %d)\n",
		   __func__, faila, failb, disks);

	if (result != 0)
		pr("%s: validation failure! faila: %d failb: %d sum_check_flags: %x\n",
		   __func__, faila, failb, result);
}
