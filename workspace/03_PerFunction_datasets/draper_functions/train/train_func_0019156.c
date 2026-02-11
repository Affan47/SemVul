ssh_knownhosts_algorithms(ssh_session session) {
  FILE *file = NULL;
  char **tokens;
  char *host;
  char *hostport;
  const char *type;
  int match;
  char **array;
  int i=0, j;

  if (session->opts.knownhosts == NULL) {
    if (ssh_options_apply(session) < 0) {
      ssh_set_error(session, SSH_REQUEST_DENIED,
          "Can't find a known_hosts file");
      return NULL;
    }
  }

  if (session->opts.host == NULL) {
    return NULL;
  }

  host = ssh_lowercase(session->opts.host);
  hostport = ssh_hostport(host, session->opts.port);
  array = malloc(sizeof(char *) * KNOWNHOSTS_MAXTYPES);

  if (host == NULL || hostport == NULL || array == NULL) {
    ssh_set_error_oom(session);
    SAFE_FREE(host);
    SAFE_FREE(hostport);
    SAFE_FREE(array);
    return NULL;
  }

  do {
    tokens = ssh_get_knownhost_line(&file,
    		session->opts.knownhosts, &type);


    if (tokens == NULL) {
      break;
    }
    match = match_hashed_host(host, tokens[0]);
    if (match == 0){
    	match = match_hostname(hostport, tokens[0], strlen(tokens[0]));
    }
    if (match == 0) {
      match = match_hostname(host, tokens[0], strlen(tokens[0]));
    }
    if (match == 0) {
      match = match_hashed_host(hostport, tokens[0]);
    }
    if (match) {

    	SSH_LOG(SSH_LOG_DEBUG, "server %s:%d has %s in known_hosts",
    							host, session->opts.port, type);

    	for(j=0;j<i && match;++j){
    		if(strcmp(array[j], type)==0)
    			match=0;
    	}
    	if (match){
    		array[i] = strdup(type);
    		i++;
    		if(i>= KNOWNHOSTS_MAXTYPES-1){
    			tokens_free(tokens);
    			break;
    		}
    	}
    }
    tokens_free(tokens);
  } while (1);

  array[i]=NULL;
  SAFE_FREE(host);
  SAFE_FREE(hostport);
  if (file != NULL) {
    fclose(file);
  }


  return array;
}
