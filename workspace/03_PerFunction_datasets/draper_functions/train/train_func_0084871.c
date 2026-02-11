edid_get_quirks(struct edid *edid)
{
	struct edid_quirk *quirk;
	int i;

	for (i = 0; i < ARRAY_SIZE(edid_quirk_list); i++) {
		quirk = &edid_quirk_list[i];

		if (edid_vendor(edid, quirk->vendor) &&
		    (EDID_PRODUCT_ID(edid) == quirk->product_id))
			return quirk->quirks;
	}

	return 0;
}
