add_to_proposal_v1_ike(proposal_t *proposal,
								   transform_substructure_t *transform)
{
	transform_attribute_type_t type;
	transform_attribute_t *tattr;
	enumerator_t *enumerator;
	u_int16_t value, key_length = 0;
	u_int16_t encr = ENCR_UNDEFINED;

	enumerator = transform->create_attribute_enumerator(transform);
	while (enumerator->enumerate(enumerator, &tattr))
	{
		type = tattr->get_attribute_type(tattr);
		value = tattr->get_value(tattr);
		switch (type)
		{
			case TATTR_PH1_ENCRYPTION_ALGORITHM:
				encr = get_alg_from_ikev1(ENCRYPTION_ALGORITHM, value);
				break;
			case TATTR_PH1_KEY_LENGTH:
				key_length = value;
				break;
			case TATTR_PH1_HASH_ALGORITHM:
				proposal->add_algorithm(proposal, INTEGRITY_ALGORITHM,
						get_alg_from_ikev1(INTEGRITY_ALGORITHM, value), 0);
				proposal->add_algorithm(proposal, PSEUDO_RANDOM_FUNCTION,
						get_alg_from_ikev1(PSEUDO_RANDOM_FUNCTION, value), 0);
				break;
			case TATTR_PH1_GROUP:
				proposal->add_algorithm(proposal, DIFFIE_HELLMAN_GROUP,
						value, 0);
				break;
			default:
				break;
		}
	}
	enumerator->destroy(enumerator);

	if (encr != ENCR_UNDEFINED)
	{
		proposal->add_algorithm(proposal, ENCRYPTION_ALGORITHM, encr, key_length);
	}
}
