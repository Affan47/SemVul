find_first_matching_mode_monochrome(stp_vars_t *v,const canon_modeuse_t* muse,const canon_cap_t *caps,const char *duplex_mode) {
  const canon_mode_t* mode=NULL;

  int i=0;
  int modefound=0;
  int j;

  stp_dprintf(STP_DBG_CANON, v,"DEBUG: Entered find_first_matching_mode_monochrome\n");

  while ( (muse->mode_name_list[i]!=NULL)  && (modefound != 1) ) {

    for(j=0;j<caps->modelist->count;j++){
      if(!strcmp(muse->mode_name_list[i],caps->modelist->modes[j].name)){

	if ( (caps->modelist->modes[j].flags & MODE_FLAG_BLACK) ) {
	  if ( (duplex_mode && strncmp(duplex_mode,"Duplex",6)) || !(muse->use_flags & DUPLEX_SUPPORT) || !(caps->modelist->modes[j].flags & MODE_FLAG_NODUPLEX) ) {

	    mode = &caps->modelist->modes[j];
	    modefound=1;
	    stp_dprintf(STP_DBG_CANON, v,"DEBUG: Gutenprint (find_first_matching_mode_monochrome): picked monochrome mode (%s)\n",mode->name);
	  }
	}
	break;
      }
    }
    i++;
  }
  return mode;
}
