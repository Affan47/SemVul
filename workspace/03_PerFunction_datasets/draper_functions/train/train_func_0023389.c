nfs4_callback_sequence(struct cb_sequenceargs *args,
			      struct cb_sequenceres *res,
			      struct cb_process_state *cps)
{
	struct nfs4_slot_table *tbl;
	struct nfs4_slot *slot;
	struct nfs_client *clp;
	int i;
	__be32 status = htonl(NFS4ERR_BADSESSION);

	clp = nfs4_find_client_sessionid(cps->net, args->csa_addr,
					 &args->csa_sessionid, cps->minorversion);
	if (clp == NULL)
		goto out;

	if (!(clp->cl_session->flags & SESSION4_BACK_CHAN))
		goto out;

	tbl = &clp->cl_session->bc_slot_table;
	slot = tbl->slots + args->csa_slotid;

	spin_lock(&tbl->slot_tbl_lock);

	if (test_bit(NFS4_SLOT_TBL_DRAINING, &tbl->slot_tbl_state)) {
		status = htonl(NFS4ERR_DELAY);


		if (test_bit(NFS4CLNT_SESSION_RESET, &clp->cl_state))
			status = htonl(NFS4ERR_BADSESSION);
		goto out_unlock;
	}

	memcpy(&res->csr_sessionid, &args->csa_sessionid,
	       sizeof(res->csr_sessionid));
	res->csr_sequenceid = args->csa_sequenceid;
	res->csr_slotid = args->csa_slotid;
	res->csr_highestslotid = NFS41_BC_MAX_CALLBACKS - 1;
	res->csr_target_highestslotid = NFS41_BC_MAX_CALLBACKS - 1;

	status = validate_seqid(tbl, args);
	if (status)
		goto out_unlock;

	cps->slotid = args->csa_slotid;


	if (referring_call_exists(clp, args->csa_nrclists, args->csa_rclists)) {
		status = htonl(NFS4ERR_DELAY);
		goto out_unlock;
	}


	slot->seq_nr++;
out_unlock:
	spin_unlock(&tbl->slot_tbl_lock);

out:
	cps->clp = clp;
	for (i = 0; i < args->csa_nrclists; i++)
		kfree(args->csa_rclists[i].rcl_refcalls);
	kfree(args->csa_rclists);

	if (status == htonl(NFS4ERR_RETRY_UNCACHED_REP)) {
		cps->drc_status = status;
		status = 0;
	} else
		res->csr_status = status;

	trace_nfs4_cb_sequence(args, res, status);
	dprintk("%s: exit with status = %d res->csr_status %d\n", __func__,
		ntohl(status), ntohl(res->csr_status));
	return status;
}
