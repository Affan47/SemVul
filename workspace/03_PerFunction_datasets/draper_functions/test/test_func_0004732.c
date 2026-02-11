pset_prop_count_elems_of_size(struct property_set *pset,
					 const char *propname, size_t length)
{
	struct property_entry *prop;

	prop = pset_prop_get(pset, propname);
	if (!prop)
		return -EINVAL;

	return prop->length / length;
}
