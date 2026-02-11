real_gretl_print_new (PrnType ptype,
				  const char *fname,
				  char *buf,
				  FILE *fp,
				  int *perr)
{
    PRN *prn = malloc(sizeof *prn);
    int err = 0;

    if (prn == NULL) {
	if (perr != NULL) {
	    *perr = E_ALLOC;
	}
	return NULL;
    }

    prn->fp = NULL;
    prn->fpaux = NULL;
    prn->buf = NULL;
    prn->bufsize = 0;
    prn->blen = 0;
    prn->savepos = -1;
    prn->format = GRETL_FORMAT_TXT;
    prn->fixed = 0;
    prn->delim = ',';
    prn->fname = NULL;

    if (ptype == GRETL_PRINT_STREAM) {
	prn->fp = fp;
    } else if (ptype == GRETL_PRINT_FILE) {
	prn->fp = gretl_fopen(fname, "w");
	if (prn->fp == NULL) {
	    err = E_FOPEN;
	    free(prn);
	    prn = NULL;
	}
    } else if (ptype == GRETL_PRINT_TEMPFILE) {
	err = prn_add_tempfile(prn);
	if (err) {
	    free(prn);
	    prn = NULL;
	} else {
	    prn->savepos = 0;
	}
    } else if (ptype == GRETL_PRINT_STDOUT) {
	prn->fp = stdout;
    } else if (ptype == GRETL_PRINT_STDERR) {
	prn->fp = stderr;
    } else if (ptype == GRETL_PRINT_BUFFER) {
	if (buf != NULL) {
	    prn->buf = buf;
	    prn->fixed = 1;
#if PRN_DEBUG
	    fprintf(stderr, "prn with fixed buffer\n");
#endif
	} else {
	    int p = pprintf(prn, "@init");

	    if (p < 0) {
		err = E_ALLOC;
		free(prn);
		prn = NULL;
	    }
	}
    }

#if PRN_DEBUG
    fprintf(stderr, "real_gretl_print_new at %p: type=%d, fname='%s', "
	    "buf=%p, fp=%p\n", (void *) prn, ptype, fname,
	    (void *) buf, (void *) fp);
#endif

    if (perr != NULL) {
	*perr = err;
    }

    return prn;
}
