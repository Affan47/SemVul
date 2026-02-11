fw_run_transaction(struct fw_card *card, int tcode, int destination_id,
		       int generation, int speed, unsigned long long offset,
		       void *payload, size_t length)
{
	struct transaction_callback_data d;
	struct fw_transaction t;

	init_timer_on_stack(&t.split_timeout_timer);
	init_completion(&d.done);
	d.payload = payload;
	fw_send_request(card, &t, tcode, destination_id, generation, speed,
			offset, payload, length, transaction_callback, &d);
	wait_for_completion(&d.done);
	destroy_timer_on_stack(&t.split_timeout_timer);

	return d.rcode;
}
