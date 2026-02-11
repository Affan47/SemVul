iscsi_tcp_segment_done(struct iscsi_tcp_conn *tcp_conn,
			   struct iscsi_segment *segment, int recv,
			   unsigned copied)
{
	struct scatterlist sg;
	unsigned int pad;

	ISCSI_DBG_TCP(tcp_conn->iscsi_conn, "copied %u %u size %u %s\n",
		      segment->copied, copied, segment->size,
		      recv ? "recv" : "xmit");
	if (segment->hash && copied) {


		iscsi_tcp_segment_unmap(segment);

		if (!segment->data) {
			sg_init_table(&sg, 1);
			sg_set_page(&sg, sg_page(segment->sg), copied,
				    segment->copied + segment->sg_offset +
							segment->sg->offset);
		} else
			sg_init_one(&sg, segment->data + segment->copied,
				    copied);
		crypto_hash_update(segment->hash, &sg, copied);
	}

	segment->copied += copied;
	if (segment->copied < segment->size) {
		iscsi_tcp_segment_map(segment, recv);
		return 0;
	}

	segment->total_copied += segment->copied;
	segment->copied = 0;
	segment->size = 0;


	iscsi_tcp_segment_unmap(segment);


	ISCSI_DBG_TCP(tcp_conn->iscsi_conn, "total copied %u total size %u\n",
		      segment->total_copied, segment->total_size);
	if (segment->total_copied < segment->total_size) {

		iscsi_tcp_segment_init_sg(segment, sg_next(segment->sg),
					  0);
		iscsi_tcp_segment_map(segment, recv);
		BUG_ON(segment->size == 0);
		return 0;
	}


	if (!(tcp_conn->iscsi_conn->session->tt->caps & CAP_PADDING_OFFLOAD)) {
		pad = iscsi_padding(segment->total_copied);
		if (pad != 0) {
			ISCSI_DBG_TCP(tcp_conn->iscsi_conn,
				      "consume %d pad bytes\n", pad);
			segment->total_size += pad;
			segment->size = pad;
			segment->data = segment->padbuf;
			return 0;
		}
	}


	if (segment->hash) {
		crypto_hash_final(segment->hash, segment->digest);
		iscsi_tcp_segment_splice_digest(segment,
				 recv ? segment->recv_digest : segment->digest);
		return 0;
	}

	return 1;
}
