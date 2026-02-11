suitable_mode_general(stp_vars_t *v,const canon_modeuse_t* muse,const canon_cap_t *caps,int quality,const char *duplex_mode) {
  const canon_mode_t* mode=NULL;
  int i=0;
  int j;
  int modefound=0;

  stp_dprintf(STP_DBG_CANON, v,"DEBUG: Entered suitable_mode_general\n");


  while ((muse->mode_name_list[i]!=NULL) && (modefound != 1)){
    for(j=0;j<caps->modelist->count;j++){
      if(!strcmp(muse->mode_name_list[i],caps->modelist->modes[j].name)){
	if ( (caps->modelist->modes[j].quality >= quality) ) {

	  if ( (duplex_mode && strncmp(duplex_mode,"Duplex",6)) || !(muse->use_flags & DUPLEX_SUPPORT) || !(caps->modelist->modes[j].flags & MODE_FLAG_NODUPLEX) ) {

	    mode = &caps->modelist->modes[j];
	    stp_dprintf(STP_DBG_CANON, v,"DEBUG: Gutenprint (suitable_mode_general): picked first mode with lowest matching quality (%s)\n",mode->name);
	    modefound=1;
	  }
	}
	break;
      }
    }
    i++;
  }
  return mode;
}
