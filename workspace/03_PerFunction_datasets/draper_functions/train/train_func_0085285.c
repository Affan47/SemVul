add_env(const char *var, const char *value)
{
    int aret;
    int i;
    char *str;
    aret = asprintf(&str, "%s=%s", var, value);
    if(aret == -1)
	errx(1, "Out of memory!");
    for(i = 0; i < num_env; i++)
	if(strncmp(env[i], var, strlen(var)) == 0 &&
	   env[i][strlen(var)] == '='){
	    free(env[i]);
	    env[i] = str;
	    return;
	}

    extend_env(str);
}
