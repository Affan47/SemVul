urlinfo_finalize (urlinfo *u, char **getbuf,
			      int err)
{
    if (u->fp != NULL) {
	fclose(u->fp);
    } else if (getbuf != NULL) {
	*getbuf = u->getbuf;
    }

    if (err && u->localfile != NULL) {
	gretl_remove(u->localfile);
    }
}
