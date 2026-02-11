do_direct_mode(struct disk *ldisks) {
  struct disk *dsk;

  for(dsk = ldisks; dsk; dsk = dsk->next) {
    display_temperature(dsk);
  }

  if(debug) {
    printf(_("\n"
	     "If one of the field value seems to match the temperature, be sure to read\n"
	     "the hddtemp man page before sending a report (section REPORT). Thanks.\n"
	     ));
  }
}
