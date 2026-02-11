gf_sc_texture_update_frame(GF_TextureHandler *txh, Bool disable_resync)
{
	u32 size, ts;


	if (txh->needs_refresh) return;

	if (!txh->stream) {
		txh->data = NULL;
		return;
	}


	if (txh->needs_release) gf_mo_release_data(txh->stream, 0xFFFFFFFF, 0);


	if (!(gf_mo_get_flags(txh->stream) & GF_MO_IS_INIT)) {


		if (txh->tx_io) {
			gf_sc_texture_release(txh);
			txh->data = NULL;
			txh->needs_refresh = 1;
		}
		if (gf_mo_is_private_media(txh->stream)) {
			setup_texture_object(txh, 1);
			gf_node_dirty_set(txh->owner, 0, 0);
		}
	}
	txh->data = gf_mo_fetch_data(txh->stream, !disable_resync, &txh->stream_finished, &ts, &size);


	if (!txh->data || !size) {
		GF_LOG(GF_LOG_INFO, GF_LOG_CODEC, ("No output frame available\n"));

		if (txh->flags & GF_SR_TEXTURE_PRIVATE_MEDIA) {

			gf_sc_invalidate(txh->compositor, NULL);
		}
		return;
	}


	if (txh->tx_io && (txh->stream_finished || (txh->last_frame_time==ts)) ) {
		gf_mo_release_data(txh->stream, 0xFFFFFFFF, 0);
		txh->needs_release = 0;
		return;
	}
	txh->needs_release = 1;
	txh->last_frame_time = ts;
	if (gf_mo_is_muted(txh->stream)) return;

	if (!txh->tx_io) {
		setup_texture_object(txh, 0);
	}


	gf_sc_texture_set_data(txh);

	txh->needs_refresh = 1;
	gf_sc_invalidate(txh->compositor, NULL);
}
