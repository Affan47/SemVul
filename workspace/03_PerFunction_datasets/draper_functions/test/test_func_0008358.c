build_payloads(private_child_delete_t *this, message_t *message)
{
	delete_payload_t *ah = NULL, *esp = NULL;
	enumerator_t *enumerator;
	child_sa_t *child_sa;

	enumerator = this->child_sas->create_enumerator(this->child_sas);
	while (enumerator->enumerate(enumerator, (void**)&child_sa))
	{
		protocol_id_t protocol = child_sa->get_protocol(child_sa);
		u_int32_t spi = child_sa->get_spi(child_sa, TRUE);

		switch (protocol)
		{
			case PROTO_ESP:
				if (esp == NULL)
				{
					esp = delete_payload_create(PLV2_DELETE, PROTO_ESP);
					message->add_payload(message, (payload_t*)esp);
				}
				esp->add_spi(esp, spi);
				DBG1(DBG_IKE, "sending DELETE for %N CHILD_SA with SPI %.8x",
							   protocol_id_names, protocol, ntohl(spi));
				break;
			case PROTO_AH:
				if (ah == NULL)
				{
					ah = delete_payload_create(PLV2_DELETE, PROTO_AH);
					message->add_payload(message, (payload_t*)ah);
				}
				ah->add_spi(ah, spi);
				DBG1(DBG_IKE, "sending DELETE for %N CHILD_SA with SPI %.8x",
							   protocol_id_names, protocol, ntohl(spi));
				break;
			default:
				break;
		}
		child_sa->set_state(child_sa, CHILD_DELETING);
	}
	enumerator->destroy(enumerator);
}
