log_append_buffer2(time_t tnl, LogBufferInfo *lbi, char *msg1, size_t size1, char *msg2, size_t size2)
{
	slapdFrontendConfig_t *slapdFrontendConfig = getFrontendConfig();
	size_t size = size1 + size2;
	char* insert_point = NULL;


    PR_Lock(lbi->lock);
    if ( ((lbi->current - lbi->top) + size > lbi->maxsize) ||
		(tnl >= loginfo.log_access_rotationsyncclock &&
		loginfo.log_access_rotationsync_enabled) ) {

        log_flush_buffer(lbi, SLAPD_ACCESS_LOG,
				0  );

    }
	insert_point = lbi->current;
	lbi->current += size;

	PR_AtomicIncrement(&(lbi->refcount));
	PR_Unlock(lbi->lock);


    memcpy(insert_point, msg1, size1);
    memcpy(insert_point + size1, msg2, size2);


	PR_AtomicDecrement(&(lbi->refcount));


    if (!slapdFrontendConfig->accesslogbuffering) {
		PR_Lock(lbi->lock);
        log_flush_buffer(lbi, SLAPD_ACCESS_LOG, 1  );
		PR_Unlock(lbi->lock);
	}

}
