ipmi_timeout_handler(ipmi_smi_t intf,
					 unsigned long timeout_period)
{
	struct list_head     timeouts;
	struct ipmi_recv_msg *msg, *msg2;
	unsigned long        flags;
	int                  i;
	unsigned int         waiting_msgs = 0;


	INIT_LIST_HEAD(&timeouts);
	spin_lock_irqsave(&intf->seq_lock, flags);
	for (i = 0; i < IPMI_IPMB_NUM_SEQ; i++)
		check_msg_timeout(intf, &(intf->seq_table[i]),
				  &timeouts, timeout_period, i,
				  &flags, &waiting_msgs);
	spin_unlock_irqrestore(&intf->seq_lock, flags);

	list_for_each_entry_safe(msg, msg2, &timeouts, link)
		deliver_err_response(msg, IPMI_TIMEOUT_COMPLETION_CODE);


	if (intf->auto_maintenance_timeout > 0) {
		spin_lock_irqsave(&intf->maintenance_mode_lock, flags);
		if (intf->auto_maintenance_timeout > 0) {
			intf->auto_maintenance_timeout
				-= timeout_period;
			if (!intf->maintenance_mode
			    && (intf->auto_maintenance_timeout <= 0)) {
				intf->maintenance_mode_enable = false;
				maintenance_mode_update(intf);
			}
		}
		spin_unlock_irqrestore(&intf->maintenance_mode_lock,
				       flags);
	}

	tasklet_schedule(&intf->recv_tasklet);

	return waiting_msgs;
}
