add_to_proposal_v1(proposal_t *proposal,
					transform_substructure_t *transform, protocol_id_t proto)
{
	transform_attribute_type_t type;
	transform_attribute_t *tattr;
	enumerator_t *enumerator;
	u_int16_t encr, value, key_length = 0;

	enumerator = transform->create_attribute_enumerator(transform);
	while (enumerator->enumerate(enumerator, &tattr))
	{
		type = tattr->get_attribute_type(tattr);
		value = tattr->get_value(tattr);
		switch (type)
		{
			case TATTR_PH2_KEY_LENGTH:
				key_length = value;
				break;
			case TATTR_PH2_AUTH_ALGORITHM:
				proposal->add_algorithm(proposal, INTEGRITY_ALGORITHM,
										get_alg_from_ikev1_auth(value), 0);
				break;
			case TATTR_PH2_GROUP:
				proposal->add_algorithm(proposal, DIFFIE_HELLMAN_GROUP,
						value, 0);
				break;
			default:
				break;
		}
	}
	enumerator->destroy(enumerator);


	proposal->add_algorithm(proposal, EXTENDED_SEQUENCE_NUMBERS,
							NO_EXT_SEQ_NUMBERS, 0);
	if (proto == PROTO_ESP)
	{
		encr = get_alg_from_ikev1_transid(ENCRYPTION_ALGORITHM,
									transform->get_transform_id(transform));
		if (encr)
		{
			proposal->add_algorithm(proposal, ENCRYPTION_ALGORITHM, encr,
									key_length);
		}
	}
}
