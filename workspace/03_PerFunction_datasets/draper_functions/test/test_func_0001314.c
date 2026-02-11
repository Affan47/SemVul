ena_com_wait_and_process_admin_cq_polling(struct ena_comp_ctx *comp_ctx,
						     struct ena_com_admin_queue *admin_queue)
{
	unsigned long flags, timeout;
	int ret;

	timeout = jiffies + usecs_to_jiffies(admin_queue->completion_timeout);

	while (1) {
		spin_lock_irqsave(&admin_queue->q_lock, flags);
		ena_com_handle_admin_completion(admin_queue);
		spin_unlock_irqrestore(&admin_queue->q_lock, flags);

		if (comp_ctx->status != ENA_CMD_SUBMITTED)
			break;

		if (time_is_before_jiffies(timeout)) {
			pr_err("Wait for completion (polling) timeout\n");

			spin_lock_irqsave(&admin_queue->q_lock, flags);
			admin_queue->stats.no_completion++;
			admin_queue->running_state = false;
			spin_unlock_irqrestore(&admin_queue->q_lock, flags);

			ret = -ETIME;
			goto err;
		}

		msleep(100);
	}

	if (unlikely(comp_ctx->status == ENA_CMD_ABORTED)) {
		pr_err("Command was aborted\n");
		spin_lock_irqsave(&admin_queue->q_lock, flags);
		admin_queue->stats.aborted_cmd++;
		spin_unlock_irqrestore(&admin_queue->q_lock, flags);
		ret = -ENODEV;
		goto err;
	}

	WARN(comp_ctx->status != ENA_CMD_COMPLETED, "Invalid comp status %d\n",
	     comp_ctx->status);

	ret = ena_com_comp_status_to_errno(comp_ctx->comp_status);
err:
	comp_ctxt_release(admin_queue, comp_ctx);
	return ret;
}
