ec_guard(struct acpi_ec *ec)
{
	unsigned long guard = usecs_to_jiffies(ec_polling_guard);
	unsigned long timeout = ec->timestamp + guard;


	do {
		if (ec_busy_polling) {

			if (ec_transaction_completed(ec))
				return 0;
			udelay(jiffies_to_usecs(guard));
		} else {


			if (!ec_transaction_polled(ec) &&
			    !acpi_ec_guard_event(ec))
				break;
			if (wait_event_timeout(ec->wait,
					       ec_transaction_completed(ec),
					       guard))
				return 0;
		}
	} while (time_before(jiffies, timeout));
	return -ETIME;
}
