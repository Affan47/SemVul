git_smart__download_pack(
	git_transport *transport,
	git_repository *repo,
	git_transfer_progress *stats,
	git_transfer_progress_callback progress_cb,
	void *progress_payload)
{
	transport_smart *t = (transport_smart *)transport;
	gitno_buffer *buf = &t->buffer;
	git_odb *odb;
	struct git_odb_writepack *writepack = NULL;
	int error = -1;
	struct network_packetsize_payload npp = {0};

	memset(stats, 0, sizeof(git_transfer_progress));

	if (progress_cb) {
		npp.callback = progress_cb;
		npp.payload = progress_payload;
		npp.stats = stats;
		t->packetsize_cb = &network_packetsize;
		t->packetsize_payload = &npp;


		if (t->buffer.offset > 0)
			t->packetsize_cb(t->buffer.offset, t->packetsize_payload);
	}

	if ((error = git_repository_odb__weakptr(&odb, repo)) < 0 ||
		((error = git_odb_write_pack(&writepack, odb, progress_cb, progress_payload)) < 0))
		goto on_error;


	if (!t->caps.side_band && !t->caps.side_band_64k) {
		if (no_sideband(t, writepack, buf, stats) < 0)
			goto on_error;

		goto on_success;
	}

	do {
		git_pkt *pkt;

		if (t->cancelled.val) {
			giterr_set(GITERR_NET, "The fetch was cancelled by the user");
			error = GIT_EUSER;
			goto on_error;
		}

		if (recv_pkt(&pkt, buf) < 0)
			goto on_error;

		if (pkt->type == GIT_PKT_PROGRESS) {
			if (t->progress_cb) {
				git_pkt_progress *p = (git_pkt_progress *) pkt;
				t->progress_cb(p->data, p->len, t->message_cb_payload);
			}
			git__free(pkt);
		} else if (pkt->type == GIT_PKT_DATA) {
			git_pkt_data *p = (git_pkt_data *) pkt;
			error = writepack->add(writepack, p->data, p->len, stats);

			git__free(pkt);
			if (error < 0)
				goto on_error;
		} else if (pkt->type == GIT_PKT_FLUSH) {

			git__free(pkt);
			break;
		}
	} while (1);

	if (writepack->commit(writepack, stats) < 0)
		goto on_error;

on_success:
	error = 0;

on_error:
	if (writepack)
		writepack->free(writepack);


	if (npp.callback && npp.stats->received_bytes > npp.last_fired_bytes)
		npp.callback(npp.stats, npp.payload);

	return error;
}
