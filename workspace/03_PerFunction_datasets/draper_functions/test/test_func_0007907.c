acpi_ec_guard_event(struct acpi_ec *ec)
{
	bool guarded = true;
	unsigned long flags;

	spin_lock_irqsave(&ec->lock, flags);


	if (ec_event_clearing == ACPI_EC_EVT_TIMING_STATUS ||
	    ec_event_clearing == ACPI_EC_EVT_TIMING_QUERY ||
	    !test_bit(EC_FLAGS_QUERY_PENDING, &ec->flags) ||
	    (ec->curr && ec->curr->command == ACPI_EC_COMMAND_QUERY))
		guarded = false;
	spin_unlock_irqrestore(&ec->lock, flags);
	return guarded;
}
