gf_term_connect_from_time_ex(GF_Terminal * term, const char *URL, u64 startTime, Bool pause_at_first_frame, Bool secondary_scene, const char *parent_path)
{
	GF_Scene *scene;
	GF_ObjectManager *odm;
	const char *main_url;
	if (!URL || !strlen(URL)) return;

	if (term->root_scene) {
		if (term->root_scene->root_od && term->root_scene->root_od->net_service) {
			main_url = term->root_scene->root_od->net_service->url;
			if (main_url && !strcmp(main_url, URL)) {
				gf_term_play_from_time(term, 0, pause_at_first_frame);
				return;
			}
		}

		gf_term_disconnect(term);
	}
	GF_LOG(GF_LOG_DEBUG, GF_LOG_MEDIA, ("[Terminal] Connecting to %s\n", URL));

	gf_term_lock_net(term, 1);
	GF_LOG(GF_LOG_DEBUG, GF_LOG_MEDIA, ("[Terminal] Creating new root scene\n", URL));

	scene = gf_scene_new(NULL);
	gf_sg_set_script_action(scene->graph, term_script_action, term);
	odm = gf_odm_new();

	scene->root_od =  odm;
	term->root_scene = scene;
	odm->parentscene = NULL;
	odm->subscene = scene;
	odm->term = term;
	GF_LOG(GF_LOG_DEBUG, GF_LOG_MEDIA, ("[Terminal] root scene created\n", URL));
	gf_term_lock_net(term, 0);

	odm->media_start_time = startTime;

	if (pause_at_first_frame)
		gf_term_set_play_state(term, GF_STATE_STEP_PAUSE, 0, 0);

	if (!strnicmp(URL, "views://", 8)) {
		odm->OD = (GF_ObjectDescriptor *)gf_odf_desc_new(GF_ODF_OD_TAG);
		gf_scene_generate_views(term->root_scene, (char *) URL+8, (char*)parent_path);
		return;
	}


	gf_term_connect_object(term, odm, (char *) URL, (char*)parent_path);
}
