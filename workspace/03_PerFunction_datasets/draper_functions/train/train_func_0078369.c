tracksource(DSPAM_CTX *CTX) {
  char ip[32];

  if (!dspam_getsource (CTX, ip, sizeof (ip)))
  {
    if (CTX->totals.innocent_learned + CTX->totals.innocent_classified > 2500) {
      if (CTX->result == DSR_ISSPAM &&
          strcmp(CTX->class, LANG_CLASS_VIRUS) != 0 &&
          _ds_match_attribute(agent_config, "TrackSources", "spam")) {
        FILE *file;
        char dropfile[MAX_FILENAME_LENGTH];
        LOG (LOG_INFO, "spam detected from %s", ip);
        if (_ds_read_attribute(agent_config, "RABLQueue")) {
          snprintf(dropfile, sizeof(dropfile), "%s/%s",
            _ds_read_attribute(agent_config, "RABLQueue"), ip);
          file = fopen(dropfile, "w");
          if (file != NULL)
            fclose(file);
        }
      } else if (CTX->result == DSR_ISSPAM &&
          strcmp(CTX->class, LANG_CLASS_VIRUS) == 0 &&
          _ds_match_attribute(agent_config, "TrackSources", "virus"))
      {
        LOG (LOG_INFO, "infected message from %s", ip);
      } else if (CTX->result != DSR_ISSPAM &&
          strcmp(CTX->class, LANG_CLASS_VIRUS) != 0 &&
          _ds_match_attribute(agent_config, "TrackSources", "nonspam"))
      {
        LOG (LOG_INFO, "innocent message from %s", ip);
      }
    }
  }
  return 0;
}
