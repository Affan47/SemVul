_job_state_unpack_one(Buf buffer)
{
	char         t1[64], t2[64], t3[64];
	job_state_t *j = xmalloc(sizeof(*j));

	safe_unpack32(    &j->jobid,      buffer);
	safe_unpack_time( &j->revoked,    buffer);
	safe_unpack_time( &j->ctime,      buffer);
	safe_unpack_time( &j->expiration, buffer);

	if (j->revoked) {
		strcpy(t2, " revoked:");
		timestr(&j->revoked, (t2+9), (64-9));
	} else {
		t2[0] = '\0';
	}
	if (j->expiration) {
		strcpy(t3, " expires:");
		timestr(&j->revoked, (t3+9), (64-9));
	} else {
		t3[0] = '\0';
	}
	debug3("cred_unpack: job %u ctime:%s%s%s",
	       j->jobid, timestr (&j->ctime, t1, 64), t2, t3);

	if ((j->revoked) && (j->expiration == (time_t) MAX_TIME)) {
		info ("Warning: revoke on job %u has no expiration",
		      j->jobid);
		j->expiration = j->revoked + 600;
	}

	return j;

unpack_error:
	_job_state_destroy(j);
	return NULL;
}
