Bnet_ReadOrder(
  DdManager * dd,
  char * ordFile,
  BnetNetwork * net,
  int  locGlob,
  int  nodrop)
{
    FILE *fp;
    st_table *dict;
    int result;
    BnetNode *node;
    char name[MAXLENGTH];

    if (ordFile == NULL) {
	return(0);
    }

    dict = st_init_table(strcmp,st_strhash);
    if (dict == NULL) {
	return(0);
    }

    if ((fp = fopen(ordFile,"r")) == NULL) {
	(void) fprintf(stderr,"Unable to open %s\n",ordFile);
	st_free_table(dict);
	return(0);
    }

    while (!feof(fp)) {
	result = fscanf(fp, "%s", name);
	if (result == EOF) {
	    break;
	} else if (result != 1) {
	    st_free_table(dict);
	    return(0);
	} else if (strlen(name) > MAXLENGTH) {
	    st_free_table(dict);
	    return(0);
	}

	if (!st_lookup(net->hash,name,&node)) {
	    (void) fprintf(stderr,"Unknown name in order file (%s)\n", name);
	    st_free_table(dict);
	    return(0);
	}

	if (st_is_member(dict,name)) {
	    (void) fprintf(stderr,"Duplicate name in order file (%s)\n", name);
	    st_free_table(dict);
	    return(0);
	}

	if (node->type != BNET_INPUT_NODE &&
	    node->type != BNET_PRESENT_STATE_NODE) {
	    (void) fprintf(stderr,"%s has the wrong type (%d)\n", name,
			   node->type);
	    st_free_table(dict);
	    return(0);
	}


	if (st_insert(dict,node->name,NULL) == ST_OUT_OF_MEM) {
	    (void) fprintf(stderr,"Out of memory in Bnet_ReadOrder\n");
	    st_free_table(dict);
	    return(0);
	}
	result = Bnet_BuildNodeBDD(dd,node,net->hash,locGlob,nodrop);
	if (result == 0) {
	    (void) fprintf(stderr,"Construction of BDD failed\n");
	    st_free_table(dict);
	    return(0);
	}
    }
    result = fclose(fp);
    if (result == EOF) {
	(void) fprintf(stderr,"Error closing order file %s\n", ordFile);
	st_free_table(dict);
	return(0);
    }


    if (st_count(dict) != net->ninputs) {
	(void) fprintf(stderr,"Order incomplete: %d names instead of %d\n",
		       st_count(dict), net->ninputs);
	st_free_table(dict);
	return(0);
    }

    st_free_table(dict);
    return(1);

}
