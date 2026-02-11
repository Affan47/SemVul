update_drift_file(double freq_ppm, double skew)
{
  struct stat buf;
  char *temp_drift_file;
  FILE *out;


  temp_drift_file = (char*) Malloc(strlen(drift_file)+8);

  if(!temp_drift_file) {
    return;
  }

  strcpy(temp_drift_file,drift_file);
  strcat(temp_drift_file,".tmp");

  out = fopen(temp_drift_file, "w");
  if (!out) {
    Free(temp_drift_file);
    LOG(LOGS_WARN, LOGF_Reference, "Could not open temporary driftfile %s.tmp for writing",
        drift_file);
    return;
  }


  if ((fprintf(out, "%20.6f %20.6f\n", freq_ppm, 1.0e6 * skew) < 0) |
      fclose(out)) {
    Free(temp_drift_file);
    LOG(LOGS_WARN, LOGF_Reference, "Could not write to temporary driftfile %s.tmp",
        drift_file);
    return;
  }


  if (!stat(drift_file,&buf)) {
    if (chown(temp_drift_file,buf.st_uid,buf.st_gid)) {
      LOG(LOGS_WARN, LOGF_Reference, "Could not change ownership of temporary driftfile %s.tmp", drift_file);
    }
    chmod(temp_drift_file,buf.st_mode&0777);
  }


  if (rename(temp_drift_file,drift_file)) {
    unlink(temp_drift_file);
    Free(temp_drift_file);
    LOG(LOGS_WARN, LOGF_Reference, "Could not replace old driftfile %s with new one %s.tmp",
        drift_file,drift_file);
    return;
  }

  Free(temp_drift_file);
}
