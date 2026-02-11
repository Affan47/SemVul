bsdsock_fake_int_handler(void)
{
	locksigqueue ();

	bsd_int_requested = 0;

	if (sbsigqueue != NULL) {
		SB;

		for (sb = sbsigqueue; sb; sb = sb->nextsig) {
			if (sb->dosignal == 1) {
				uae_Signal (sb->ownertask, sb->sigstosend);
				sb->sigstosend = 0;
			}
			sb->dosignal = 0;
		}

		sbsigqueue = NULL;
	}

	unlocksigqueue ();
}
