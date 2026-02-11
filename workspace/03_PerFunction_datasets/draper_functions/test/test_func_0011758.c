istgt_lu_create_threads(ISTGT_Ptr istgt, int new_only)
{
#ifdef HAVE_PTHREAD_SET_NAME_NP
	char buf[MAX_TMPBUF];
#endif
	ISTGT_LU_Ptr lu;
	int rc;
	int i;

	ISTGT_TRACELOG(ISTGT_TRACE_DEBUG, "istgt_lu_create_threads\n");

	for (i = 0; i < MAX_LOGICAL_UNIT; i++) {
		lu = istgt->logical_unit[i];
		if (lu == NULL)
			continue;
		if (new_only && !lu->to_add) {
			ISTGT_TRACELOG(ISTGT_TRACE_DEBUG, "skip existing LUN %d\n", i);
			continue;
		}

		if (lu->queue_depth != 0) {

#ifdef ISTGT_STACKSIZE
			rc = pthread_create(&lu->thread, &istgt->attr, &luworker, (void *)lu);
#else
			rc = pthread_create(&lu->thread, NULL, &luworker, (void *)lu);
#endif
			if (rc != 0) {
				ISTGT_ERRLOG("pthread_create() failed\n");
				return -1;
			}
#if 0
			rc = pthread_detach(lu->thread);
			if (rc != 0) {
				ISTGT_ERRLOG("pthread_detach() failed\n");
				return -1;
			}
#endif
#ifdef HAVE_PTHREAD_SET_NAME_NP
			snprintf(buf, sizeof buf, "luthread #%d", i);
			pthread_set_name_np(lu->thread, buf);
#endif
		}
	}

	return 0;
}
