coll_copy_attributes (const char *key, xmmsv_t *val, void *udata)
{
	const char *value;

	if (xmmsv_get_string (val, &value)) {
		xmmsv_coll_attribute_set ((xmmsv_coll_t *) udata, key, value);
	}
}
