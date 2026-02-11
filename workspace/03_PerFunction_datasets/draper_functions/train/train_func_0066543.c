bau_process_message(struct msg_desc *mdp, struct bau_control *bcp,
						int do_acknowledge)
{
	short socket_ack_count = 0;
	short *sp;
	struct atomic_short *asp;
	struct ptc_stats *stat = bcp->statp;
	struct bau_pq_entry *msg = mdp->msg;
	struct bau_control *smaster = bcp->socket_master;


	if (msg->address == TLB_FLUSH_ALL) {
		local_flush_tlb();
		stat->d_alltlb++;
	} else {
		__flush_tlb_one(msg->address);
		stat->d_onetlb++;
	}
	stat->d_requestee++;


	if (msg->msg_type == MSG_RETRY && bcp == bcp->uvhub_master)
		bau_process_retry_msg(mdp, bcp);


	sp = &smaster->socket_acknowledge_count[mdp->msg_slot];
	asp = (struct atomic_short *)sp;
	socket_ack_count = atom_asr(1, asp);
	if (socket_ack_count == bcp->cpus_in_socket) {
		int msg_ack_count;


		*sp = 0;
		asp = (struct atomic_short *)&msg->acknowledge_count;
		msg_ack_count = atom_asr(socket_ack_count, asp);

		if (msg_ack_count == bcp->cpus_in_uvhub) {


			reply_to_message(mdp, bcp, do_acknowledge);
		}
	}

	return;
}
