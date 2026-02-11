conv_input_closer(ScmPort *p)
{
    ScmConvInfo *info = (ScmConvInfo*)p->src.buf.data;
    jconv_close(info);
    if (info->ownerp) {
        Scm_ClosePort(info->remote);
        info->remoteClosed = TRUE;
    }
}
