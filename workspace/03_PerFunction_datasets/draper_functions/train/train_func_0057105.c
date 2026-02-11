mbcport_dyn_cast(ScmCharPort *cport, const ScmCharPortVTbl *dst_vptr)
{
    return (dst_vptr == ScmBaseCharPort_vptr
            || dst_vptr == ScmMultiByteCharPort_vptr) ? cport : NULL;
}
