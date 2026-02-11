gf_term_reload_cfg(GF_Terminal *term)
{
	const char *sOpt;
	u32 mode;
	s32 prio;

	if (!term) return;


	sOpt = gf_cfg_get_key(term->user->config, "Systems", "AlwaysDrawBIFS");
	if (sOpt && !stricmp(sOpt, "yes"))
		term->flags &= ~GF_TERM_SYSDEC_RESYNC;
	else
		term->flags |= GF_TERM_SYSDEC_RESYNC;

	sOpt = gf_cfg_get_key(term->user->config, "Systems", "ForceSingleClock");
	if (sOpt && !stricmp(sOpt, "yes"))
		term->flags |= GF_TERM_SINGLE_CLOCK;
	else
		term->flags &= ~GF_TERM_SINGLE_CLOCK;

	sOpt = gf_cfg_get_key(term->user->config, "Systems", "TimeSlice");
	if (!sOpt) {
		sOpt = "30";
		gf_cfg_set_key(term->user->config, "Systems", "TimeSlice", "30");
	}
	term->frame_duration = atoi(sOpt);

	if (!(term->user->init_flags & GF_TERM_NO_DECODER_THREAD) ){
		prio = GF_THREAD_PRIORITY_NORMAL;
		sOpt = gf_cfg_get_key(term->user->config, "Systems", "Priority");
		if (sOpt) {
			if (!stricmp(sOpt, "low")) prio = GF_THREAD_PRIORITY_LOWEST;
			else if (!stricmp(sOpt, "normal")) prio = GF_THREAD_PRIORITY_NORMAL;
			else if (!stricmp(sOpt, "high")) prio = GF_THREAD_PRIORITY_HIGHEST;
			else if (!stricmp(sOpt, "real-time")) prio = GF_THREAD_PRIORITY_REALTIME;
		} else {
			gf_cfg_set_key(term->user->config, "Systems", "Priority", "normal");
		}
		gf_term_set_priority(term, prio);

		sOpt = gf_cfg_get_key(term->user->config, "Systems", "ThreadingPolicy");
		if (sOpt) {
			mode = GF_TERM_THREAD_FREE;
			if (!stricmp(sOpt, "Single")) mode = GF_TERM_THREAD_SINGLE;
			else if (!stricmp(sOpt, "Multi")) mode = GF_TERM_THREAD_MULTI;
			gf_term_set_threading(term, mode);
		}
	}


	term->net_data_timeout = 20000;
	sOpt = gf_cfg_get_key(term->user->config, "Network", "DataTimeout");
	if (sOpt) term->net_data_timeout = atoi(sOpt);

	if (term->root_scene) gf_scene_set_duration(term->root_scene);

#ifndef GPAC_DISABLE_SVG
	if (term->dcci_doc) {
		sOpt = gf_cfg_get_key(term->user->config, "General", "EnvironmentFile");
		gf_sg_reload_xml_doc(sOpt, term->dcci_doc);
	}
#endif

	gf_term_load_shortcuts(term);


	gf_sc_set_option(term->compositor, GF_OPT_RELOAD_CONFIG, 1);
}
