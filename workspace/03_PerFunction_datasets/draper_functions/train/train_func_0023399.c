drill_stats_add_to_drill_counter(gerbv_drill_list_t *drill_list_in,
				 int drill_num_in,
				 int increment) {

    gerbv_drill_list_t *drill;
    for(drill = drill_list_in; drill != NULL; drill = drill->next) {
	if (drill_num_in == drill->drill_num) {
	    dprintf("    In drill_stats_add_to_drill_counter, adding increment = %d drills to drill list\n", increment);
	    drill->drill_count += increment;
	    return;
	}
    }
}
