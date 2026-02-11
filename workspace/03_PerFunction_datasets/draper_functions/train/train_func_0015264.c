_add_pvs(struct cmd_context *cmd, struct pv_segment *peg,
		    uint32_t s __attribute__((unused)), void *data)
{
	struct seg_pvs *spvs = (struct seg_pvs *) data;
	struct pv_list *pvl;


	if (find_pv_in_pv_list(&spvs->pvs, peg->pv))
			return 1;

	if (!(pvl = dm_pool_alloc(cmd->mem, sizeof(*pvl)))) {
		log_error("pv_list allocation failed");
		return 0;
	}

	pvl->pv = peg->pv;

	dm_list_add(&spvs->pvs, &pvl->list);

	return 1;
}
