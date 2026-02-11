do_shutdown(long long action,
            enum crmd_fsa_cause cause,
            enum crmd_fsa_state cur_state, enum crmd_fsa_input current_input, fsa_data_t * msg_data)
{

    set_bit(fsa_input_register, R_SHUTDOWN);

    if (is_heartbeat_cluster()) {
        if (is_set(fsa_input_register, pe_subsystem->flag_connected)) {
            crm_info("Terminating the %s", pe_subsystem->name);
            if (stop_subsystem(pe_subsystem, TRUE) == FALSE) {

                crm_err("Faking %s exit", pe_subsystem->name);
                clear_bit(fsa_input_register, pe_subsystem->flag_connected);
            } else {
                crm_info("Waiting for subsystems to exit");
                crmd_fsa_stall(FALSE);
            }
        }
        crm_info("All subsystems stopped, continuing");
    }

    if (stonith_api) {

        clear_bit(fsa_input_register, R_ST_REQUIRED);

        crm_info("Disconnecting STONITH...");
        stonith_api->cmds->disconnect(stonith_api);
    }
}
