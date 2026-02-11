ADIOI_cb_config_list_parse(char *config_list,
			 ADIO_cb_name_array array,
			 int ranklist[],
			 int cb_nodes)
{
    int token, max_procs, cur_rank = 0, nr_procnames;
    char *cur_procname, *cur_procname_p, **procnames;
    char *used_procnames;

    nr_procnames = array->namect;
    procnames = array->names;


    cur_procname = ADIOI_Malloc((MPI_MAX_INFO_VAL+1) * sizeof(char));
    if (cur_procname == NULL) {
	return -1;
    }

    yylval = ADIOI_Malloc((MPI_MAX_INFO_VAL+1) * sizeof(char));
    if (yylval == NULL) {
	ADIOI_Free(cur_procname);
	return -1;
    }

    token_ptr = config_list;


    if (cb_nodes > nr_procnames) cb_nodes = nr_procnames;


    used_procnames = ADIOI_Malloc(array->namect * sizeof(char));
    if (used_procnames == NULL) {
	ADIOI_Free(cur_procname);
	ADIOI_Free(yylval);
	yylval = NULL;
	return -1;
    }
    memset(used_procnames, 0, array->namect);


    if (strcmp(config_list, "*:*") == 0) {
	for (cur_rank = 0; cur_rank < cb_nodes; cur_rank++) {
	    ranklist[cur_rank] = cur_rank;
	}
	ADIOI_Free(cur_procname);
	ADIOI_Free(yylval);
	yylval = NULL;
    	ADIOI_Free(used_procnames);
	return cb_nodes;
    }

    while (cur_rank < cb_nodes) {
	token = cb_config_list_lex();

	if (token == AGG_EOS) {
	    ADIOI_Free(cur_procname);
	    ADIOI_Free(yylval);
	    yylval = NULL;
    	    ADIOI_Free(used_procnames);
	    return cur_rank;
	}

	if (token != AGG_WILDCARD && token != AGG_STRING) {

	    FPRINTF(stderr, "error parsing config list\n");
	    ADIOI_Free(cur_procname);
	    ADIOI_Free(yylval);
	    yylval = NULL;
    	    ADIOI_Free(used_procnames);
	    return cur_rank;
	}

	if (token == AGG_WILDCARD) {
	    cur_procname_p = NULL;
	}
	else {


	    strcpy(cur_procname, yylval);
	    cur_procname_p = cur_procname;
	}


	max_procs = get_max_procs(cb_nodes);

#ifdef CB_CONFIG_LIST_DEBUG
	if (token == AGG_WILDCARD) {
	    FPRINTF(stderr, "looking for *:%d\n", max_procs);
	}
	else {
	    FPRINTF(stderr, "looking for %s:%d\n", cur_procname, max_procs);
	}
#endif


	match_procs(cur_procname_p, max_procs, procnames, used_procnames,
		    nr_procnames, ranklist, cb_nodes, &cur_rank);
    }
    ADIOI_Free(cur_procname);
    ADIOI_Free(yylval);
    yylval = NULL;
    ADIOI_Free(used_procnames);
    return cur_rank;
}
