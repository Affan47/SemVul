rar_close(struct archfile *fil)
{
    struct rarfile *rfil = (struct rarfile *) fil->data;

    if(rfil != NULL) {
        close(rfil->fd);
        av_del_tmpfile(rfil->tmpfile);
        av_free(rfil);
    }

    return 0;
}
