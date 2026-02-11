matcherprop_match_test(const MatcherProp *prop,
					  MsgInfo *info)
{
	gchar *file;
	gchar *cmd;
	gint retval;
#ifdef USE_PTHREAD
	pthread_t pt;
	pthread_attr_t pta;
	thread_data *td = g_new0(thread_data, 1);
	void *res = NULL;
	time_t start_time = time(NULL);
#endif

	file = procmsg_get_message_file(info);
	if (file == NULL) {
#ifdef USE_PTHREAD
		g_free(td);
#endif
		return FALSE;
	}
	g_free(file);

	cmd = matching_build_command(prop->expr, info);
	if (cmd == NULL) {
#ifdef USE_PTHREAD
		g_free(td);
#endif
		return FALSE;
}

#ifdef USE_PTHREAD

	if (debug_filtering_session
			&& prefs_common.filtering_debug_level >= FILTERING_DEBUG_LEVEL_HIGH) {
		log_print(LOG_DEBUG_FILTERING,
				"starting threaded command [ %s ]\n",
				cmd);
	}

	td->cmd = cmd;
	td->done = FALSE;
	if (pthread_attr_init(&pta) != 0 ||
	    pthread_attr_setdetachstate(&pta, PTHREAD_CREATE_JOINABLE) != 0 ||
	    pthread_create(&pt, &pta, matcher_test_thread, td) != 0)
		retval = system(cmd);
	else {
		debug_print("waiting for test thread\n");
		while(!td->done) {

			claws_do_idle();
			if (time(NULL) - start_time > 30) {
				pthread_cancel(pt);
				td->done = TRUE;
				retval = -1;
			}
		}
		pthread_join(pt, &res);
		retval = GPOINTER_TO_INT(res);
		debug_print(" test thread returned %d\n", retval);
	}
	g_free(td);
#else

	if (debug_filtering_session
			&& prefs_common.filtering_debug_level >= FILTERING_DEBUG_LEVEL_HIGH) {
		log_print(LOG_DEBUG_FILTERING,
				"starting synchronous command [ %s ]\n",
				cmd);
	}

	retval = system(cmd);
#endif
	debug_print("Command exit code: %d\n", retval);


	if (debug_filtering_session
			&& prefs_common.filtering_debug_level >= FILTERING_DEBUG_LEVEL_HIGH) {
		log_print(LOG_DEBUG_FILTERING,
				"command returned [ %d ]\n",
				retval);
	}

	g_free(cmd);
	return (retval == 0);
}
