nhrp_payload_free(struct nhrp_payload *payload)
{
	struct nhrp_cie *cie, *n;

	switch (payload->payload_type) {
	case NHRP_PAYLOAD_TYPE_RAW:
		nhrp_buffer_free(payload->u.raw);
		break;
	case NHRP_PAYLOAD_TYPE_CIE_LIST:
		list_for_each_entry_safe(cie, n, &payload->u.cie_list, cie_list_entry) {
			list_del(&cie->cie_list_entry);
			nhrp_cie_free(cie);
		}
		break;
	}
	payload->payload_type = NHRP_PAYLOAD_TYPE_NONE;
}
