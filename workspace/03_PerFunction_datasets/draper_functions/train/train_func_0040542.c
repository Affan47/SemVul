start_write_thread(struct ftpfs_file *fh)
{
	if (fh->write_conn != NULL)
	{
		fprintf(stderr, "assert fh->write_conn == NULL failed!\n");
		exit(1);
	}

	fh->written_flag=0;
	fh->isready=0;
	fh->eof=0;
	sem_init(&fh->data_avail, 0, 0);
	sem_init(&fh->data_need, 0, 0);
	sem_init(&fh->data_written, 0, 0);
	sem_init(&fh->ready, 0, 0);

    fh->write_conn = curl_easy_init();
    if (fh->write_conn == NULL) {
      fprintf(stderr, "Error initializing libcurl\n");
      return 0;
    } else {
      int err;
      set_common_curl_stuff(fh->write_conn);
      err = pthread_create(&fh->thread_id, NULL, ftpfs_write_thread, fh);
      if (err) {
        fprintf(stderr, "failed to create thread: %s\n", strerror(err));

        return 0;
      }
    }
	return 1;
}
