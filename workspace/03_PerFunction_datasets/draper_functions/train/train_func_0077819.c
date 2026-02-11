gf_cm_set_eos(GF_CompositionMemory *cb)
{
	gf_odm_lock(cb->odm, 1);


	if (cb->Status == CB_BUFFER) {
		cb->Status = CB_BUFFER_DONE;
		gf_clock_buffer_off(cb->odm->codec->ck);
		cb->odm->codec->ck->data_timeout = 0;
		GF_LOG(GF_LOG_DEBUG, GF_LOG_SYNC, ("[SyncLayer] ODM%d: buffering off at %d (nb buffering on clock: %d)\n", cb->odm->OD->objectDescriptorID, gf_term_get_time(cb->odm->term), cb->odm->codec->ck->Buffering));
	}
	cb->HasSeenEOS = 1;
	gf_term_invalidate_compositor(cb->odm->term);
	gf_odm_lock(cb->odm, 0);
}
