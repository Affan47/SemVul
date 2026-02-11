proposal_substructure_create_for_ipcomp_v1(
			u_int32_t lifetime, u_int64_t lifebytes, u_int16_t cpi,
			ipsec_mode_t mode, encap_t udp, u_int8_t proposal_number)
{
	private_proposal_substructure_t *this;
	transform_substructure_t *transform;


	this = (private_proposal_substructure_t*)
						proposal_substructure_create(PLV1_PROPOSAL_SUBSTRUCTURE);


	transform = transform_substructure_create_type(PLV1_TRANSFORM_SUBSTRUCTURE,
												   1, IKEV1_IPCOMP_DEFLATE);

	transform->add_transform_attribute(transform,
		transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
							TATTR_PH2_ENCAP_MODE, get_ikev1_mode(mode, udp)));
	if (lifetime)
	{
		transform->add_transform_attribute(transform,
			transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
							TATTR_PH2_SA_LIFE_TYPE, IKEV1_LIFE_TYPE_SECONDS));
		transform->add_transform_attribute(transform,
			transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
							TATTR_PH2_SA_LIFE_DURATION, lifetime));
	}
	if (lifebytes)
	{
		transform->add_transform_attribute(transform,
			transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
							TATTR_PH2_SA_LIFE_TYPE, IKEV1_LIFE_TYPE_KILOBYTES));
		transform->add_transform_attribute(transform,
			transform_attribute_create_value(PLV1_TRANSFORM_ATTRIBUTE,
							TATTR_PH2_SA_LIFE_DURATION, lifebytes / 1000));
	}

	add_transform_substructure(this, transform);

	this->spi = chunk_clone(chunk_from_thing(cpi));
	this->spi_size = this->spi.len;
	this->protocol_id = PROTO_IPCOMP;
	this->proposal_number = proposal_number;

	compute_length(this);

	return &this->public;
}
