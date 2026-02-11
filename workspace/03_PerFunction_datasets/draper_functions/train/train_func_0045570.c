cl_cvdparse(const char *head)
{
	struct cl_cvd *cvd;
	char *pt;


    if(strncmp(head, "ClamAV-VDB:", 11)) {
	cli_errmsg("cli_cvdparse: Not a CVD file\n");
	return NULL;
    }

    if(!(cvd = (struct cl_cvd *) cli_malloc(sizeof(struct cl_cvd)))) {
	cli_errmsg("cl_cvdparse: Can't allocate memory for cvd\n");
	return NULL;
    }

    if(!(cvd->time = cli_strtok(head, 1, ":"))) {
	cli_errmsg("cli_cvdparse: Can't parse the creation time\n");
	free(cvd);
	return NULL;
    }

    if(!(pt = cli_strtok(head, 2, ":"))) {
	cli_errmsg("cli_cvdparse: Can't parse the version number\n");
	free(cvd->time);
	free(cvd);
	return NULL;
    }
    cvd->version = atoi(pt);
    free(pt);

    if(!(pt = cli_strtok(head, 3, ":"))) {
	cli_errmsg("cli_cvdparse: Can't parse the number of signatures\n");
	free(cvd->time);
	free(cvd);
	return NULL;
    }
    cvd->sigs = atoi(pt);
    free(pt);

    if(!(pt = cli_strtok(head, 4, ":"))) {
	cli_errmsg("cli_cvdparse: Can't parse the functionality level\n");
	free(cvd->time);
	free(cvd);
	return NULL;
    }
    cvd->fl = atoi(pt);
    free(pt);

    if(!(cvd->md5 = cli_strtok(head, 5, ":"))) {
	cli_errmsg("cli_cvdparse: Can't parse the MD5 checksum\n");
	free(cvd->time);
	free(cvd);
	return NULL;
    }

    if(!(cvd->dsig = cli_strtok(head, 6, ":"))) {
	cli_errmsg("cli_cvdparse: Can't parse the digital signature\n");
	free(cvd->time);
	free(cvd->md5);
	free(cvd);
	return NULL;
    }

    if(!(cvd->builder = cli_strtok(head, 7, ":"))) {
	cli_errmsg("cli_cvdparse: Can't parse the builder name\n");
	free(cvd->time);
	free(cvd->md5);
	free(cvd->dsig);
	free(cvd);
	return NULL;
    }

    if((pt = cli_strtok(head, 8, ":"))) {
	cvd->stime = atoi(pt);
	free(pt);
    } else {
	cli_dbgmsg("cli_cvdparse: No creation time in seconds (old file format)\n");
	cvd->stime = 0;
    }

    return cvd;
}
