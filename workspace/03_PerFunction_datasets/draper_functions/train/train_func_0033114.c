compare(const struct ebt_entry_match *m1,
   const struct ebt_entry_match *m2)
{
	struct ebt_802_3_info *info1 = (struct ebt_802_3_info *)m1->data;
	struct ebt_802_3_info *info2 = (struct ebt_802_3_info *)m2->data;

	if (info1->bitmask != info2->bitmask)
		return 0;
	if (info1->invflags != info2->invflags)
		return 0;
	if (info1->bitmask & EBT_802_3_SAP) {
		if (info1->sap != info2->sap)
			return 0;
	}
	if (info1->bitmask & EBT_802_3_TYPE) {
		if (info1->type != info2->type)
			return 0;
	}
	return 1;
}
