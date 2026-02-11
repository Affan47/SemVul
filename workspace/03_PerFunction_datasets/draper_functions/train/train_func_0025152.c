make_cluster(struct config_group *g,
					 const char *name)
{
	struct dlm_cluster *cl = NULL;
	struct dlm_spaces *sps = NULL;
	struct dlm_comms *cms = NULL;
	void *gps = NULL;

	cl = kzalloc(sizeof(struct dlm_cluster), GFP_NOFS);
	gps = kcalloc(3, sizeof(struct config_group *), GFP_NOFS);
	sps = kzalloc(sizeof(struct dlm_spaces), GFP_NOFS);
	cms = kzalloc(sizeof(struct dlm_comms), GFP_NOFS);

	if (!cl || !gps || !sps || !cms)
		goto fail;

	config_group_init_type_name(&cl->group, name, &cluster_type);
	config_group_init_type_name(&sps->ss_group, "spaces", &spaces_type);
	config_group_init_type_name(&cms->cs_group, "comms", &comms_type);

	cl->group.default_groups = gps;
	cl->group.default_groups[0] = &sps->ss_group;
	cl->group.default_groups[1] = &cms->cs_group;
	cl->group.default_groups[2] = NULL;

	cl->cl_tcp_port = dlm_config.ci_tcp_port;
	cl->cl_buffer_size = dlm_config.ci_buffer_size;
	cl->cl_rsbtbl_size = dlm_config.ci_rsbtbl_size;
	cl->cl_recover_timer = dlm_config.ci_recover_timer;
	cl->cl_toss_secs = dlm_config.ci_toss_secs;
	cl->cl_scan_secs = dlm_config.ci_scan_secs;
	cl->cl_log_debug = dlm_config.ci_log_debug;
	cl->cl_protocol = dlm_config.ci_protocol;
	cl->cl_timewarn_cs = dlm_config.ci_timewarn_cs;
	cl->cl_waitwarn_us = dlm_config.ci_waitwarn_us;
	cl->cl_new_rsb_count = dlm_config.ci_new_rsb_count;
	cl->cl_recover_callbacks = dlm_config.ci_recover_callbacks;
	memcpy(cl->cl_cluster_name, dlm_config.ci_cluster_name,
	       DLM_LOCKSPACE_LEN);

	space_list = &sps->ss_group;
	comm_list = &cms->cs_group;
	return &cl->group;

 fail:
	kfree(cl);
	kfree(gps);
	kfree(sps);
	kfree(cms);
	return ERR_PTR(-ENOMEM);
}
