rsh_get(struct remote *rem, struct remgetparam *gp)
{
    int res;
    struct rshlocalfile *lf;
    char *tmpfile;
    char *codedpath;
    char *path;
    const char *prog[4];
    char progname[4];

    strcpy(progname, "rcp");
    progname[0] = rem->name[0];

    res = av_get_tmpfile(&tmpfile);
    if(res < 0)
	return res;

    AV_NEW_OBJ(lf, rsh_free_localfile);
    lf->pr = NULL;

    codedpath = rsh_code_name(gp->hostpath.path);
    path = av_stradd(NULL, gp->hostpath.host, ":", codedpath, NULL);
    av_free(codedpath);

    lf->tmpfile = tmpfile;

    prog[0] = progname;
    prog[1] = path;
    prog[2] = lf->tmpfile;
    prog[3] = NULL;

    res = av_start_program(prog, &lf->pr);
    av_free(path);
    if(res < 0) {
        av_unref_obj(lf);
        av_del_tmpfile(tmpfile);
        return res;
    }

    lf->currsize = 0;

    gp->data = lf;
    gp->localname = lf->tmpfile;

    return 0;
}
