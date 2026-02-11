ike_sa_id_hash(ike_sa_id_t *ike_sa_id)
{


	if (ike_sa_id->get_ike_version(ike_sa_id) == IKEV1_MAJOR_VERSION ||
		ike_sa_id->is_initiator(ike_sa_id))
	{
		return ike_sa_id->get_initiator_spi(ike_sa_id);
	}
	return ike_sa_id->get_responder_spi(ike_sa_id);
}
