rocker_tx_desc_frags_unmap(const struct rocker_port *rocker_port,
				       const struct rocker_desc_info *desc_info)
{
	const struct rocker *rocker = rocker_port->rocker;
	struct pci_dev *pdev = rocker->pdev;
	const struct rocker_tlv *attrs[ROCKER_TLV_TX_MAX + 1];
	struct rocker_tlv *attr;
	int rem;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_TX_MAX, desc_info);
	if (!attrs[ROCKER_TLV_TX_FRAGS])
		return;
	rocker_tlv_for_each_nested(attr, attrs[ROCKER_TLV_TX_FRAGS], rem) {
		const struct rocker_tlv *frag_attrs[ROCKER_TLV_TX_FRAG_ATTR_MAX + 1];
		dma_addr_t dma_handle;
		size_t len;

		if (rocker_tlv_type(attr) != ROCKER_TLV_TX_FRAG)
			continue;
		rocker_tlv_parse_nested(frag_attrs, ROCKER_TLV_TX_FRAG_ATTR_MAX,
					attr);
		if (!frag_attrs[ROCKER_TLV_TX_FRAG_ATTR_ADDR] ||
		    !frag_attrs[ROCKER_TLV_TX_FRAG_ATTR_LEN])
			continue;
		dma_handle = rocker_tlv_get_u64(frag_attrs[ROCKER_TLV_TX_FRAG_ATTR_ADDR]);
		len = rocker_tlv_get_u16(frag_attrs[ROCKER_TLV_TX_FRAG_ATTR_LEN]);
		pci_unmap_single(pdev, dma_handle, len, DMA_TO_DEVICE);
	}
}
