set_distrib_bits(struct cpumask *flush_mask, struct bau_control *bcp,
			struct bau_desc *bau_desc, int *localsp, int *remotesp)
{
	int cpu;
	int pnode;
	int cnt = 0;
	struct hub_and_pnode *hpp;

	for_each_cpu(cpu, flush_mask) {


		hpp = &bcp->socket_master->thp[cpu];
		pnode = hpp->pnode - bcp->partition_base_pnode;
		bau_uvhub_set(pnode, &bau_desc->distribution);
		cnt++;
		if (hpp->uvhub == bcp->uvhub)
			(*localsp)++;
		else
			(*remotesp)++;
	}
	if (!cnt)
		return 1;
	return 0;
}
