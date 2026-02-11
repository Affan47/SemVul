reset_project(PROJECT* project, bool detaching) {
    unsigned int i;
    APP_VERSION* avp;
    APP* app;
    vector<APP*>::iterator app_iter;
    vector<APP_VERSION*>::iterator avp_iter;
    RESULT* rp;
    PERS_FILE_XFER* pxp;

    msg_printf(project, MSG_INFO, "Resetting project");
    active_tasks.abort_project(project);


    for (i=0; i<pers_file_xfers->pers_file_xfers.size(); i++) {
        pxp = pers_file_xfers->pers_file_xfers[i];
        if (pxp->fip->project == project) {
            if (pxp->fxp) {
                file_xfers->remove(pxp->fxp);
                delete pxp->fxp;
            }
            pers_file_xfers->remove(pxp);
            delete pxp;
            i--;
        }
    }


    scheduler_op->abort(project);


    for (i=0; i<results.size(); i++) {
        rp = results[i];
        if (rp->project == project) {
            rp->got_server_ack = true;
        }
    }

    project->user_files.clear();
    project->project_files.clear();


    for (i=0; i<file_infos.size(); i++) {
        FILE_INFO* fip = file_infos[i];
        if (fip->project == project) {
            fip->sticky = false;
        }
    }

    garbage_collect_always();


    if (!project->anonymous_platform || detaching) {
        avp_iter = app_versions.begin();
        while (avp_iter != app_versions.end()) {
            avp = *avp_iter;
            if (avp->project == project) {
                avp_iter = app_versions.erase(avp_iter);
                delete avp;
            } else {
                avp_iter++;
            }
        }

        app_iter = apps.begin();
        while (app_iter != apps.end()) {
            app = *app_iter;
            if (app->project == project) {
                app_iter = apps.erase(app_iter);
                delete app;
            } else {
                app_iter++;
            }
        }
        garbage_collect_always();
    }


    project->scheduler_urls.clear();

    project->duration_correction_factor = 1;
    project->ams_resource_share = -1;
    project->min_rpc_time = 0;
    project->pwf.reset(project);
    for (int j=0; j<coprocs.n_rsc; j++) {
        project->rsc_pwf[j].reset();
    }
    write_state_file();
    return 0;
}
