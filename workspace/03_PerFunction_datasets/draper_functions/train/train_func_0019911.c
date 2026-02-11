gdlm_mount(struct gfs2_sbd *sdp, const char *table)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	char cluster[GFS2_LOCKNAME_LEN];
	const char *fsname;
	uint32_t flags;
	int error, ops_result;


	INIT_DELAYED_WORK(&sdp->sd_control_work, gfs2_control_func);
	spin_lock_init(&ls->ls_recover_spin);
	ls->ls_recover_flags = 0;
	ls->ls_recover_mount = 0;
	ls->ls_recover_start = 0;
	ls->ls_recover_block = 0;
	ls->ls_recover_size = 0;
	ls->ls_recover_submit = NULL;
	ls->ls_recover_result = NULL;
	ls->ls_lvb_bits = NULL;

	error = set_recover_size(sdp, NULL, 0);
	if (error)
		goto fail;


	fsname = strchr(table, ':');
	if (!fsname) {
		fs_info(sdp, "no fsname found\n");
		error = -EINVAL;
		goto fail_free;
	}
	memset(cluster, 0, sizeof(cluster));
	memcpy(cluster, table, strlen(table) - strlen(fsname));
	fsname++;

	flags = DLM_LSFL_FS | DLM_LSFL_NEWEXCL;


	error = dlm_new_lockspace(fsname, cluster, flags, GDLM_LVB_SIZE,
				  &gdlm_lockspace_ops, sdp, &ops_result,
				  &ls->ls_dlm);
	if (error) {
		fs_err(sdp, "dlm_new_lockspace error %d\n", error);
		goto fail_free;
	}

	if (ops_result < 0) {


		fs_info(sdp, "dlm lockspace ops not used\n");
		free_recover_size(ls);
		set_bit(DFL_NO_DLM_OPS, &ls->ls_recover_flags);
		return 0;
	}

	if (!test_bit(SDF_NOJOURNALID, &sdp->sd_flags)) {
		fs_err(sdp, "dlm lockspace ops disallow jid preset\n");
		error = -EINVAL;
		goto fail_release;
	}


	error = control_mount(sdp);
	if (error) {
		fs_err(sdp, "mount control error %d\n", error);
		goto fail_release;
	}

	ls->ls_first = !!test_bit(DFL_FIRST_MOUNT, &ls->ls_recover_flags);
	clear_bit(SDF_NOJOURNALID, &sdp->sd_flags);
	smp_mb__after_atomic();
	wake_up_bit(&sdp->sd_flags, SDF_NOJOURNALID);
	return 0;

fail_release:
	dlm_release_lockspace(ls->ls_dlm, 2);
fail_free:
	free_recover_size(ls);
fail:
	return error;
}
