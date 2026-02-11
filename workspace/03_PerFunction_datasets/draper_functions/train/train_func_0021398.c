mp_bundle_terminated()
{
	TDB_DATA key;

	bundle_terminating = 1;
	upper_layers_down(0);
	notice("Connection terminated.");
	print_link_stats();
	if (!demand) {
		remove_pidfiles();
		script_unsetenv("IFNAME");
	}

	lock_db();
	destroy_bundle();
	iterate_bundle_links(sendhup);
	key.dptr = blinks_id;
	key.dsize = strlen(blinks_id);
	tdb_delete(pppdb, key);
	unlock_db();

	new_phase(PHASE_DEAD);

	doing_multilink = 0;
	multilink_master = 0;
}
