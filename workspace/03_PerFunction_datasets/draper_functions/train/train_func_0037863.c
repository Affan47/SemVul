cb2(void* arg)
{
    int ret;
    out(arg); out(" (in cb2)\n");
    ret = cr_replace_self(cb4, "XXX self/THREAD not overwritten by CONTINUE", CR_THREAD_CONTEXT);
    if (ret) {
        printf("XXX cr_replace_self() cb2/pre returned %d w/ errno=%d(%s)\n", ret, errno, cr_strerror(errno));
    }
    ret = cr_checkpoint(0);
    if (ret) {
        printf("XXX cr_checkpoint() unexpectedy returned %d in cb2\n", ret);
    }
    ret = cr_replace_self(cb4, "005 self/THREAD from CONTINUE section", CR_THREAD_CONTEXT);
    if (ret) {
        printf("XXX cr_replace_self() cb2/post returned %d w/ errno=%d(%s)\n", ret, errno, cr_strerror(errno));
    }
    return 0;
}
