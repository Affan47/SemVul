add_old_result(RESULT& r) {
    while (!old_results.empty()) {
        OLD_RESULT& ores = *old_results.begin();
        if (ores.create_time < gstate.now - 3600) {
            old_results.pop_front();
        } else {
            break;
        }
    }
    OLD_RESULT ores;
    strcpy(ores.project_url, r.project->master_url);
    strcpy(ores.result_name, r.name);
    strcpy(ores.app_name, r.app->name);
    ores.elapsed_time = r.final_elapsed_time;
    ores.cpu_time = r.final_cpu_time;
    ores.completed_time = r.completed_time;
    ores.create_time = gstate.now;
    ores.exit_status = r.exit_status;
    old_results.push_back(ores);
}
