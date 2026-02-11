sinfo_detnoise_free(detnoise_config * cfg)
{
  int i=0;
  if(cfg != NULL) {
    for(i=0;i<cfg->nframes;i++){
      if(cfg->framelist[i] != NULL) cpl_free(cfg->framelist[i]);
    }
    if(cfg->framelist) {
      if(cfg->framelist != NULL) cpl_free(cfg->framelist);
    }
    sinfo_detnoise_cfg_destroy(cfg);
  }
}
