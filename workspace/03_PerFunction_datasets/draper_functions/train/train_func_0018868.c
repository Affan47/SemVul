fc_fcp_send_abort(struct fc_fcp_pkt *fsp)
{
	if (!fsp->seq_ptr)
		return -EINVAL;

	per_cpu_ptr(fsp->lp->stats, get_cpu())->FcpPktAborts++;
	put_cpu();

	fsp->state |= FC_SRB_ABORT_PENDING;
	return fsp->lp->tt.seq_exch_abort(fsp->seq_ptr, 0);
}
