reread1Wct(Wct *pwct)
{
    int fd, rc;


    pwct->fsize = fsize(pwct->fname);
    pwct->ftime = ftime(pwct->fname);


    if (pwct->fimage)
        free(pwct->fimage);
    pwct->fimage = (char *) malloc(pwct->fsize + 1);
    if (pwct->fimage == 0)
        sfatal("Cannot allocate new table.");
    pwct->fimage[pwct->fsize] = 0;


    fd = open(pwct->fname, O_RDONLY);
    if (fd == -1)
        fatal("Cannot read file %s.", pwct->fname);
    rc = read(fd, pwct->fimage, pwct->fsize);
    if (rc != pwct->fsize)
        fatal("Did not read all of file %s.", pwct->fname);

    return pwct;
}
