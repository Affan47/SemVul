msg_copied_p2( sync_vars_t *svars, sync_rec_t *srec, int t, message_t *tmsg, int uid )
{
	if (srec->uid[t] != uid) {
		debug( "  -> new UID %d\n", uid );
		Fprintf( svars->jfp, "%c %d %d %d\n", "<>"[t], srec->uid[M], srec->uid[S], uid );
		srec->uid[t] = uid;
		srec->tuid[0] = 0;
	}
	if (!tmsg->srec) {
		tmsg->srec = srec;
		if (svars->maxuid[1-t] < tmsg->uid) {
			svars->maxuid[1-t] = tmsg->uid;
			Fprintf( svars->jfp, "%c %d\n", ")("[t], tmsg->uid );
		}
	}
}
