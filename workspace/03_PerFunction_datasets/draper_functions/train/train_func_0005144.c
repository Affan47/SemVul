check_map_iit (IIT_T map_iit, IIT_T chromosome_iit) {
  char *typestring, *lookup, *p;
  int type, destranded_len;
  bool errorp = false;

  for (type = 1; type < IIT_ntypes(map_iit); type++) {
    lookup = typestring = IIT_typestring(map_iit,type);
    if ((p = rindex(typestring,'+')) != NULL) {
      destranded_len = (p - typestring)/sizeof(char);
      lookup = (char *) CALLOC(destranded_len+1,sizeof(char));
      strncpy(lookup,typestring,destranded_len);
    } else if ((p = rindex(typestring,'-')) != NULL) {
      destranded_len = (p - typestring)/sizeof(char);
      lookup = (char *) CALLOC(destranded_len+1,sizeof(char));
      strncpy(lookup,typestring,destranded_len);
    }

    if (IIT_find_one(chromosome_iit,lookup) < 0) {
      if (p != NULL) {
	fprintf(stderr,"Warning: In %s, type %s (without the %s) does not correspond to a known chromosome in %s.\n",
		map_iitfile,typestring,p,dbversion);
      } else {
	fprintf(stderr,"Warning: In %s, type %s does not correspond to a known chromosome in %s.\n",
		map_iitfile,typestring,dbversion);
      }
      errorp = true;
    }

    if (p != NULL) {
      FREE(lookup);
    }
  }
  if (errorp == true) {
    fprintf(stderr,"Known chromosomes: ");
    IIT_dump_labels(stderr,chromosome_iit);
  }
  return;
}
