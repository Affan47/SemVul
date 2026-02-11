filtprog_startput(void *data, void **resp)
{
    int res;
    struct filtprog *fp = (struct filtprog *) data;
    struct filtconn *fc;

    res = av_ftruncate(fp->vf, 0);
    if(res < 0)
        return res;

    res = filtprog_start(fp, fp->filtdat->revprog, &fc);
    if(res < 0)
        return res;

    *resp = fc;

    return 0;
}
