acpi_ec_transaction_unlocked(struct acpi_ec *ec,
					struct transaction *t)
{
	unsigned long tmp;
	int ret = 0;


	spin_lock_irqsave(&ec->lock, tmp);

	if (!acpi_ec_submit_flushable_request(ec)) {
		ret = -EINVAL;
		goto unlock;
	}
	ec_dbg_ref(ec, "Increase command");

	ec->curr = t;
	ec_dbg_req("Command(%s) started", acpi_ec_cmd_string(t->command));
	start_transaction(ec);
	spin_unlock_irqrestore(&ec->lock, tmp);

	ret = ec_poll(ec);

	spin_lock_irqsave(&ec->lock, tmp);
	if (t->irq_count == ec_storm_threshold)
		acpi_ec_clear_storm(ec, EC_FLAGS_COMMAND_STORM);
	ec_dbg_req("Command(%s) stopped", acpi_ec_cmd_string(t->command));
	ec->curr = NULL;

	acpi_ec_complete_request(ec);
	ec_dbg_ref(ec, "Decrease command");
unlock:
	spin_unlock_irqrestore(&ec->lock, tmp);
	return ret;
}
