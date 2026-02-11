Clipped_Format (Clipped clipped, struct fmt_info *p)
{
    Object render, clipping;
    int rc;

    DXGetClippedInfo(clipped, &render, &clipping);
    rc = _dxfObject_Format(clipping, p);
    if (rc != OK)
	return ERROR;
    rc = _dxfObject_Format(render, p);
    if (rc != OK)
	return ERROR;

    fprintf(p->fp, "object %s class clipped ", objid(p, (Object)clipped));
    fprintf(p->fp, "by %s ", objid(p, clipping));
    fprintf(p->fp, "of %s\n", objid(p, render));
    return OK;

}
