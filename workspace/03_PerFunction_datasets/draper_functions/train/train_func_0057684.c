scan_idlelist(server_rec * main_server)
{


    fcgid_procnode *previous_node, *current_node, *next_node;
    fcgid_procnode *error_list_header;
    fcgid_procnode *proc_table;
    apr_time_t last_active_time, start_time;
    apr_time_t now = apr_time_now();
    int idle_timeout, proc_lifetime;
    fcgid_server_conf *sconf =
        ap_get_module_config(main_server->module_config,
                             &fcgid_module);


    if (procmgr_must_exit()
        || apr_time_sec(now) - apr_time_sec(lastidlescan) <=
        sconf->idle_scan_interval)
        return;
    lastidlescan = now;


    proc_table = proctable_get_table_array();
    previous_node = proctable_get_idle_list();
    error_list_header = proctable_get_error_list();

    proctable_pm_lock(main_server);
    current_node = &proc_table[previous_node->next_index];
    while (current_node != proc_table) {
        next_node = &proc_table[current_node->next_index];
        last_active_time = current_node->last_active_time;
        start_time = current_node->start_time;
        idle_timeout = current_node->cmdopts.idle_timeout;
        proc_lifetime = current_node->cmdopts.proc_lifetime;
        if (((idle_timeout &&
              (apr_time_sec(now) - apr_time_sec(last_active_time) >
               idle_timeout))
             || (proc_lifetime
                 && (apr_time_sec(now) - apr_time_sec(start_time) >
                     proc_lifetime)))
            && is_kill_allowed(main_server, current_node)) {

            if (idle_timeout &&
                (apr_time_sec(now) - apr_time_sec(last_active_time) >
                 idle_timeout))
                current_node->diewhy = FCGID_DIE_IDLE_TIMEOUT;
            else if (proc_lifetime &&
                     (apr_time_sec(now) - apr_time_sec(start_time) >
                      proc_lifetime))
                current_node->diewhy = FCGID_DIE_LIFETIME_EXPIRED;


            previous_node->next_index = current_node->next_index;


            current_node->next_index = error_list_header->next_index;
            error_list_header->next_index = current_node - proc_table;
        }
        else
            previous_node = current_node;

        current_node = next_node;
    }
    proctable_pm_unlock(main_server);
}
