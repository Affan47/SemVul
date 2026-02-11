set_from_proposal_v1_ike(private_proposal_substructure_t *this,
									 proposal_t *proposal, u_int32_t lifetime,
									 auth_method_t method, int number)
{
	transform_substructure_t *transform;
	u_int16_t alg, key_size;
	enumerator_t *enumerator;

	transform = transform_substructure_create_type(PLV1_TRANSFORM_SUBSTRUCTURE,
												number, IKEV1_TRANSID_KEY_IKE);

	enumerator = proposal->create_enumerator(proposal, ENCRYPTION_ALGORITHM);
	while (enumerator->enumerate(enumerator, &alg, &key_size))
	{
		alg = get_ikev1_from_alg(ENCRYPTION_ALGORITHM, alg);
		if (alg)
		{
			transform->add_transform_attribute(transform,
				transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
									TATTR_PH1_ENCRYPTION_ALGORITHM, alg));
			if (key_size)
			{
				transform->add_transform_attribute(transform,
					transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
										TATTR_PH1_KEY_LENGTH, key_size));
			}
			break;
		}
	}
	enumerator->destroy(enumerator);


	enumerator = proposal->create_enumerator(proposal, INTEGRITY_ALGORITHM);
	while (enumerator->enumerate(enumerator, &alg, &key_size))
	{
		alg = get_ikev1_from_alg(INTEGRITY_ALGORITHM, alg);
		if (alg)
		{
			transform->add_transform_attribute(transform,
				transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
									TATTR_PH1_HASH_ALGORITHM, alg));
			break;
		}
	}
	enumerator->destroy(enumerator);

	enumerator = proposal->create_enumerator(proposal, DIFFIE_HELLMAN_GROUP);
	if (enumerator->enumerate(enumerator, &alg, &key_size))
	{
		transform->add_transform_attribute(transform,
			transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
								TATTR_PH1_GROUP, alg));
	}
	enumerator->destroy(enumerator);

	transform->add_transform_attribute(transform,
		transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
							TATTR_PH1_AUTH_METHOD, get_ikev1_auth(method)));
	transform->add_transform_attribute(transform,
		transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
							TATTR_PH1_LIFE_TYPE, IKEV1_LIFE_TYPE_SECONDS));
	transform->add_transform_attribute(transform,
		transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
							TATTR_PH1_LIFE_DURATION, lifetime));

	add_transform_substructure(this, transform);
}
