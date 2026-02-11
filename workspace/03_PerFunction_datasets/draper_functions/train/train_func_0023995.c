of_nvmem_device_get(struct device_node *np, const char *id)
{

	struct device_node *nvmem_np;
	int index;

	index = of_property_match_string(np, "nvmem-names", id);

	nvmem_np = of_parse_phandle(np, "nvmem", index);
	if (!nvmem_np)
		return ERR_PTR(-EINVAL);

	return __nvmem_device_get(nvmem_np, NULL, NULL);
}
