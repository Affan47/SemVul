do_next_tlv(const VALUE_PAIR *vp, const VALUE_PAIR *next, int nest)
{
	unsigned int tlv1, tlv2;

	if (nest > fr_attr_max_tlv) return 0;

	if (!vp) return 0;


	if (!next) return 0;


	if (vp->vendor != next->vendor) return 0;


	tlv1 = vp->attribute;
	tlv2 = next->attribute;

	tlv1 &= ((1 << fr_attr_shift[nest]) - 1);
	tlv2 &= ((1 << fr_attr_shift[nest]) - 1);

	if (tlv1 != tlv2) return 0;

	return 1;
}
