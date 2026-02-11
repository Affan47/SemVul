quirk_amd_mmconfig_area(struct pnp_dev *dev)
{
	resource_size_t start, end;
	struct pnp_resource *pnp_res;
	struct resource *res;
	struct resource mmconfig_res, *mmconfig;

	mmconfig = amd_get_mmconfig_range(&mmconfig_res);
	if (!mmconfig)
		return;

	list_for_each_entry(pnp_res, &dev->resources, list) {
		res = &pnp_res->res;
		if (res->end < mmconfig->start || res->start > mmconfig->end ||
		    (res->start == mmconfig->start && res->end == mmconfig->end))
			continue;

		dev_info(&dev->dev, FW_BUG
			 "%pR covers only part of AMD MMCONFIG area %pR; adding more reservations\n",
			 res, mmconfig);
		if (mmconfig->start < res->start) {
			start = mmconfig->start;
			end = res->start - 1;
			pnp_add_mem_resource(dev, start, end, 0);
		}
		if (mmconfig->end > res->end) {
			start = res->end + 1;
			end = mmconfig->end;
			pnp_add_mem_resource(dev, start, end, 0);
		}
		break;
	}
}
