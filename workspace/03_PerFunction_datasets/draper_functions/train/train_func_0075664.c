tradspool_freearticle(ARTHANDLE *article)
{
    PRIV_TRADSPOOL *private;

    if (article == NULL)
        return;

    if (article->private) {
	private = (PRIV_TRADSPOOL *) article->private;
	if (private->mmapped)
	    munmap(private->artbase, private->artlen);
	else
	    free(private->artbase);
	if (private->curdir)
	    closedir(private->curdir);
	free(private->curdirname);
        free(private);
    }
    free(article);
}
