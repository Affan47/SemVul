pack_float_XBGR16161616_UNORM(const GLfloat src[4], void *dst)
{
   GLushort *d = ((GLushort *) dst);
   UNCLAMPED_FLOAT_TO_USHORT(d[0], src[RCOMP]);
   UNCLAMPED_FLOAT_TO_USHORT(d[1], src[GCOMP]);
   UNCLAMPED_FLOAT_TO_USHORT(d[2], src[BCOMP]);
   d[3] = 65535;
}
