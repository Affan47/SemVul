check_all() {
    unsigned int i;
    for (i=0; i<apps.size(); i++) {
        check_app(*apps[i]);
    }
    for (i=0; i<file_infos.size(); i++) {
        check_file_info(*file_infos[i]);
    }
    for (i=0; i<app_versions.size(); i++) {
        check_app_version(*app_versions[i]);
    }
    for (i=0; i<workunits.size(); i++) {
        check_workunit(*workunits[i]);
    }
    for (i=0; i<results.size(); i++) {
        check_result(*results[i]);
    }
    for (i=0; i<active_tasks.active_tasks.size(); i++) {
        check_active_task(*active_tasks.active_tasks[i]);
    }
    for (i=0; i<pers_file_xfers->pers_file_xfers.size(); i++) {
        check_pers_file_xfer(*pers_file_xfers->pers_file_xfers[i]);
    }
    for (i=0; i<file_xfers->file_xfers.size(); i++) {
        check_file_xfer(*file_xfers->file_xfers[i]);
    }
}
