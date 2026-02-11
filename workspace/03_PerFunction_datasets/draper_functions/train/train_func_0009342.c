marshall_cie(uint8_t **pdu, size_t *pduleft, struct nhrp_cie *cie)
{
	cie->hdr.nbma_address_len = cie->nbma_address.addr_len;
	cie->hdr.nbma_subaddress_len = cie->nbma_address.subaddr_len;
	cie->hdr.protocol_address_len = cie->protocol_address.addr_len;

	if (!marshall_binary(pdu, pduleft, sizeof(struct nhrp_cie_header), &cie->hdr))
		return FALSE;
	if (!marshall_nbma_address(pdu, pduleft, &cie->nbma_address))
		return FALSE;
	return marshall_protocol_address(pdu, pduleft, &cie->protocol_address);
}
