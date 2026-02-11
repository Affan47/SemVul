link_terminated(unit)
    int unit;
{
    if (phase == PHASE_DEAD || phase == PHASE_MASTER)
	return;
    new_phase(PHASE_DISCONNECT);

    if (pap_logout_hook) {
	pap_logout_hook();
    }
    session_end(devnam);

    if (!doing_multilink) {
	notice("Connection terminated.");
	print_link_stats();
    } else
	notice("Link terminated.");


    if (!doing_multilink && !demand)
	remove_pidfiles();


    if (fd_ppp >= 0) {
	remove_fd(fd_ppp);
	clean_check();
	the_channel->disestablish_ppp(devfd);
	if (doing_multilink)
	    mp_exit_bundle();
	fd_ppp = -1;
    }
    if (!hungup)
	lcp_lowerdown(0);
    if (!doing_multilink && !demand)
	script_unsetenv("IFNAME");


    if (devfd >= 0 && the_channel->disconnect) {
	the_channel->disconnect();
	devfd = -1;
    }
    if (the_channel->cleanup)
	(*the_channel->cleanup)();

    if (doing_multilink && multilink_master) {
	if (!bundle_terminating)
	    new_phase(PHASE_MASTER);
	else
	    mp_bundle_terminated();
    } else
	new_phase(PHASE_DEAD);
}
