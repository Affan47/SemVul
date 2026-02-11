handle_exclusive_region_request(struct fw_card *card,
					    struct fw_packet *p,
					    struct fw_request *request,
					    unsigned long long offset)
{
	struct fw_address_handler *handler;
	int tcode, destination, source;

	destination = HEADER_GET_DESTINATION(p->header[0]);
	source      = HEADER_GET_SOURCE(p->header[1]);
	tcode       = HEADER_GET_TCODE(p->header[0]);
	if (tcode == TCODE_LOCK_REQUEST)
		tcode = 0x10 + HEADER_GET_EXTENDED_TCODE(p->header[3]);

	rcu_read_lock();
	handler = lookup_enclosing_address_handler(&address_handler_list,
						   offset, request->length);
	if (handler)
		handler->address_callback(card, request,
					  tcode, destination, source,
					  p->generation, offset,
					  request->data, request->length,
					  handler->callback_data);
	rcu_read_unlock();

	if (!handler)
		fw_send_response(card, request, RCODE_ADDRESS_ERROR);
}
