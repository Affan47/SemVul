dna_notice_allocation(struct configEntry *config_entry, PRUint64 new,
                                  PRUint64 last)
{

    if ((new != 0) && (new <= (config_entry->maxval + config_entry->interval))) {
        config_entry->nextval = new;
    }


    if ((last == config_entry->maxval) ||
        (config_entry->nextval > config_entry->maxval)) {


        if (config_entry->next_range_lower != 0) {

            if (dna_activate_next_range(config_entry) != 0) {
                slapi_log_error(SLAPI_LOG_FATAL, DNA_PLUGIN_SUBSYSTEM,
                                "dna_notice_allocation: Unable to activate "
                                "the next range for range %s.\n", config_entry->dn);
            }
        } else {
            config_entry->remaining = 0;

            dna_update_shared_config(config_entry);
        }
    } else {
        if (config_entry->next_range_lower != 0) {
            config_entry->remaining = ((config_entry->maxval - config_entry->nextval + 1) /
                                    config_entry->interval) + ((config_entry->next_range_upper -
                                    config_entry->next_range_lower +1) / config_entry->interval);
        } else {
            config_entry->remaining = ((config_entry->maxval - config_entry->nextval + 1) /
                                    config_entry->interval);
        }


        dna_update_shared_config(config_entry);
    }

    return;
}
