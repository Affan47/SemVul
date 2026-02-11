transaction_callback(struct fw_card *card, int rcode,
				 void *payload, size_t length, void *data)
{
	struct transaction_callback_data *d = data;

	if (rcode == RCODE_COMPLETE)
		memcpy(d->payload, payload, length);
	d->rcode = rcode;
	complete(&d->done);
}
