get_nat_oa_payload_type(ike_sa_t *ike_sa)
{
	if (ike_sa->supports_extension(ike_sa, EXT_NATT_DRAFT_02_03))
	{
		return PLV1_NAT_OA_DRAFT_00_03;
	}
	return PLV1_NAT_OA;
}
