tcm_loop_tpg_attrib_fabric_prot_type_store(
		struct config_item *item, const char *page, size_t count)
{
	struct se_portal_group *se_tpg = attrib_to_tpg(item);
	struct tcm_loop_tpg *tl_tpg = container_of(se_tpg, struct tcm_loop_tpg,
						   tl_se_tpg);
	unsigned long val;
	int ret = kstrtoul(page, 0, &val);

	if (ret) {
		pr_err("kstrtoul() returned %d for fabric_prot_type\n", ret);
		return ret;
	}
	if (val != 0 && val != 1 && val != 3) {
		pr_err("Invalid qla2xxx fabric_prot_type: %lu\n", val);
		return -EINVAL;
	}
	tl_tpg->tl_fabric_prot_type = val;

	return count;
}
