run_amz_file(clamz_downloader *dl,
			const clamz_config *cfg,
			FILE *amzfile,
			const char *fname)
{
  char *inbuf;
  unsigned char *xml;
  size_t sz;
  clamz_playlist *pl;
  int i;
  int status, rv = 0;
  char *logname;
  FILE *logfile;

  sz = 0;
  inbuf = NULL;

  while (!feof(amzfile) && !ferror(amzfile)) {
    if (inbuf)
      inbuf = realloc(inbuf, (sz + 1024) * sizeof(char));
    else
      inbuf = malloc((sz + 1024) * sizeof(char));
    sz += fread(&inbuf[sz], 1, 1024, amzfile);
  }

  if (amzfile != stdin)
    fclose(amzfile);

  if (cfg->printonly && cfg->printasxml) {
    xml = decrypt_amz_file(inbuf, sz, fname);
    if (!xml) {
      free(inbuf);
      return 2;
    }

    printf("%s", xml);
    free(xml);
    free(inbuf);
    return 0;
  }
  else {
    if (!cfg->printonly) {
      if (write_backup_file(inbuf, sz, getbasename(fname))) {
        free(inbuf);
        return 3;
      }
    }

    pl = new_playlist();

    if (read_amz_file(pl, inbuf, sz, fname)) {
      free(inbuf);
      free_playlist(pl);
      return 2;
    }

    if (!cfg->printonly) {
      logname = get_config_file_name("logs", getbasename(fname), ".log");
      if (!logname) {
        free(inbuf);
	return 1;
      }

      logfile = fopen(logname, "w");
      if (!logfile) {
	perror(logname);
	free(logname);
        free(inbuf);
	return 3;
      }

      free(logname);
      set_download_log_file(dl, logfile);
    }
    else {
      logfile = NULL;
    }

    if (cfg->printonly || cfg->verbose)
      print_pl_info(pl, fname);

    for (i = 0; i < pl->num_tracks; i++) {
      if (cfg->printonly || cfg->verbose)
        print_tr_info(pl->tracks[i], i + 1);

      status = download_track(dl, pl->tracks[i]);
      if (!rv)
        rv = status;
      fputc('\n', stderr);
    }

    set_download_log_file(dl, NULL);

    free(inbuf);
    free_playlist(pl);
    if (logfile)
      fclose(logfile);
    return rv;
  }
}
