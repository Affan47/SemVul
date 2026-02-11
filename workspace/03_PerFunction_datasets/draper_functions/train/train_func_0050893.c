dbzinit(const char *name)
{
    char *fname;

    if (opendb) {
	warn("dbzinit: dbzinit already called once");
	errno = 0;
	return false;
    }


    fname = concat(name, dir, (char *) 0);
    if ((dirf = Fopen(fname, "r+", DBZ_DIR)) == NULL) {
	dirf = Fopen(fname, "r", DBZ_DIR);
	readonly = true;
    } else
	readonly = false;
    free(fname);
    if (dirf == NULL) {
	syswarn("dbzinit: can't open .dir file");
	return false;
    }
    close_on_exec(fileno(dirf), true);


    if (!getconf(dirf, &conf)) {
	warn("dbzinit: getconf failure");
	Fclose(dirf);
	errno = EDOM;
	return false;
    }


#ifdef	DO_TAGGED_HASH
    if (!openhashtable(name, pag, &pagtab, SOF, options.pag_incore)) {
	Fclose(dirf);
	return false;
    }
    if (!openbasefile(name)) {
	close(pagtab.fd);
	Fclose(dirf);
	return false;
    }
    tagbits = conf.tagmask << conf.tagshift;
    taghere = conf.tagenb << conf.tagshift;
    tagboth = tagbits | taghere;
    canttag_warned = 0;
#else
    if (!openhashtable(name, idx, &idxtab, sizeof(of_t), options.pag_incore)) {
	Fclose(dirf);
	return false;
    }
    if (!openhashtable(name, exists, &etab, sizeof(erec),
		options.exists_incore)) {
	Fclose(dirf);
	return false;
    }
#endif


    dirty = false;
    opendb = true;
    prevp = FRESH;
    memset(&empty_rec, '\0', sizeof(empty_rec));
    debug("dbzinit: succeeded");
    return true;
}
