alvarion_vsa_hack(VALUE_PAIR *vp)
{
	int		vendorcode;
	int		number = 1;

	for ( ; vp != NULL; vp = vp->next) {
		DICT_ATTR *da;

		vendorcode = VENDOR(vp->attribute);
		if (vendorcode != 12394) continue;
		if (vp->type != PW_TYPE_STRING) continue;

		da = dict_attrbyvalue(number | (12394 << 16));
		if (!da) continue;

		vp->attribute = da->attr;
		vp->name = da->name;

		number++;
	}
}
