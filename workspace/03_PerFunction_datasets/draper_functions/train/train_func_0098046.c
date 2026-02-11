CopyProjectsToStateBuffer(PROJECTS& p, CC_STATE& state) {
    int retval = 0;
    unsigned int i;
    PROJECT* state_project = NULL;


    for (i=0; i<state.projects.size(); i++) {
        state_project = state.projects[i];
        state_project->flag_for_delete = true;
    }

    for (i=0; i<p.projects.size(); i++) {
        state_project = state.lookup_project(p.projects[i]->master_url);
        if (state_project && (!strcmp(p.projects[i]->master_url, state_project->master_url))) {


            *state_project = *(p.projects[i]);
            state_project->flag_for_delete = false;
        } else {
            retval = ERR_NOT_FOUND;
        }
        continue;
    }


    if (!retval) {
        for (i=0; i<state.projects.size(); i++) {
            state_project = state.projects[i];
            if (state_project->flag_for_delete) {
                retval = ERR_FILE_MISSING;
            }
        }
    }

    return retval;
}
