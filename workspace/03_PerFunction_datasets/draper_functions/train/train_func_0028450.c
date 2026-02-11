gck_attribute_init_ulong (GckAttribute *attr,
                          gulong attr_type,
                          gulong value)
{
	CK_ULONG val = value;
	g_return_if_fail (attr != NULL);
	gck_attribute_init (attr, attr_type, (const guchar *)&val, sizeof (val));
}
