comparesha(const char *diff)
{
	char info[32], buff[FILEBUFF], *sha, *pt, *name;
	const char *tokens[3];
	FILE *fh;
	int ret = 0, tokens_count;

    name = strdup(diff);
    if(!name) {
	mprintf("!verifydiff: strdup() failed\n");
	return -1;
    }
    if(!(pt = strrchr(name, '-')) || !isdigit(pt[1])) {
	mprintf("!verifydiff: Invalid diff name\n");
	free(name);
	return -1;
    }
    *pt = 0;
    if((pt = strrchr(name, *PATHSEP)))
	pt++;
    else
	pt = name;

    snprintf(info, sizeof(info), "%s.info", pt);
    free(name);

    if(!(fh = fopen(info, "rb"))) {
	mprintf("!verifydiff: Can't open %s\n", info);
	return -1;
    }

    if(!fgets(buff, sizeof(buff), fh) || strncmp(buff, "ClamAV-VDB", 10)) {
	mprintf("!verifydiff: Incorrect info file %s\n", info);
	fclose(fh);
	return -1;
    }

    while(fgets(buff, sizeof(buff), fh)) {
	cli_chomp(buff);
	tokens_count = cli_strtokenize(buff, ':', 3, tokens);
	if(tokens_count != 3) {
	    if(!strcmp(tokens[0], "DSIG"))
		continue;
	    mprintf("!verifydiff: Incorrect format of %s\n", info);
	    ret = -1;
	    break;
	}
	if(!(sha = sha256file(tokens[0], NULL))) {
	    mprintf("!verifydiff: Can't generate SHA256 for %s\n", buff);
	    ret = -1;
	    break;
	}
	if(strcmp(sha, tokens[2])) {
	    mprintf("!verifydiff: %s has incorrect checksum\n", buff);
	    ret = -1;
	    free(sha);
	    break;
	}
	free(sha);
    }

    fclose(fh);
    return ret;
}
