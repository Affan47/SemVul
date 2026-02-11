log_shutdown (MonoProfiler *prof)
{
	in_shutdown = 1;
#ifndef DISABLE_HELPER_THREAD
	if (prof->command_port) {
		char c = 1;
		void *res;
		write (prof->pipes [1], &c, 1);
		pthread_join (prof->helper_thread, &res);
	}
#endif
#if USE_PERF_EVENTS
	if (perf_data) {
		int i;
		for (i = 0; i < num_perf; ++i)
			read_perf_mmap (prof, i);
	}
#endif
	dump_sample_hits (prof, prof->stat_buffers, 1);
	take_lock ();
	if (TLS_GET (tlsbuffer))
		dump_buffer (prof, TLS_GET (tlsbuffer));
	TLS_SET (tlsbuffer, NULL);
	release_lock ();
#if defined (HAVE_SYS_ZLIB)
	if (prof->gzfile)
		gzclose (prof->gzfile);
#endif
	if (prof->pipe_output)
		pclose (prof->file);
	else
		fclose (prof->file);
	free (prof);
}
