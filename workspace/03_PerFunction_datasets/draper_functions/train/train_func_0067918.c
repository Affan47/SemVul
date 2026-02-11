gf_bifs_decoder_new(GF_SceneGraph *scenegraph, Bool command_dec)
{
	GF_BifsDecoder *tmp;
	GF_SAFEALLOC(tmp, GF_BifsDecoder);

	tmp->QPs = gf_list_new();
	tmp->streamInfo = gf_list_new();
	tmp->info = NULL;

	tmp->pCurrentProto = NULL;
	tmp->scenegraph = scenegraph;
	tmp->command_buffers = gf_list_new();
	if (command_dec) {
		tmp->dec_memory_mode = 1;
		tmp->force_keep_qp = 1;
	}
	tmp->current_graph = NULL;
	return tmp;
}
