gck_attribute_init_invalid (GckAttribute *attr,
                            gulong attr_type)
{
	g_return_if_fail (attr != NULL);
	attr->type = attr_type;
	attr->value = NULL;
	attr->length = G_MAXULONG;
}
