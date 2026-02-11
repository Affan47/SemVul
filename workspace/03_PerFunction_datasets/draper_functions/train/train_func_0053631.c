drill_stats_increment_drill_counter(gerbv_drill_list_t *drill_list_in,
				    int drill_num_in) {

    dprintf("   ----> Entering drill_stats_increment_drill_counter......\n");

    gerbv_drill_list_t *drill;
    for(drill = drill_list_in; drill != NULL; drill = drill->next) {
	if (drill_num_in == drill->drill_num) {
	    drill->drill_count++;
	    dprintf("         .... incrementing drill count.  drill_num = %d, drill_count = %d.\n",
		    drill_list_in->drill_num, drill->drill_count);
	    dprintf("   <---- .... Leaving drill_stats_increment_drill_counter after incrementing counter.\n");
	    return;
	}
    }
    dprintf("   <---- .... Leaving drill_stats_increment_drill_counter without incrementing any counter.\n");

}
