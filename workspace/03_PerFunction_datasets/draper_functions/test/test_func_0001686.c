unregister_rpc(servtab_t *sep)
{
	int n;

	for (n = sep->se_rpcver_lo; n <= sep->se_rpcver_hi; n++) {
		if (!pmap_unset(sep->se_rpcprog, n))
			bb_perror_msg("pmap_unset(%u,%u)", sep->se_rpcprog, n);
	}
}
