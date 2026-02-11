process_certreqs(private_isakmp_cert_pre_t *this, message_t *message)
{
	enumerator_t *enumerator;
	payload_t *payload;
	auth_cfg_t *auth;

	auth = this->ike_sa->get_auth_cfg(this->ike_sa, TRUE);

	enumerator = message->create_payload_enumerator(message);
	while (enumerator->enumerate(enumerator, &payload))
	{
		switch (payload->get_type(payload))
		{
			case PLV1_CERTREQ:
			{
				certificate_t *cert;

				this->ike_sa->set_condition(this->ike_sa,
											COND_CERTREQ_SEEN, TRUE);
				cert = find_certificate(this, (certreq_payload_t*)payload);
				if (cert)
				{
					auth->add(auth, AUTH_RULE_CA_CERT, cert);
				}
				break;
			}
			default:
				break;
		}
	}
	enumerator->destroy(enumerator);
}
