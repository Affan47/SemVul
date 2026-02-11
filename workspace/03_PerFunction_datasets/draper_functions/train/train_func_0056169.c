s3_del_seg(AFFILE *af,const char *segname)
{
    struct s3_private *sp =S3_PRIVATE(af);
    sp->current_seg = segname;
    return object_rm(sp->bucket,sp->path + sp->current_seg);
}
