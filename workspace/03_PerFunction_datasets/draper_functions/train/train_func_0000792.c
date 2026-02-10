CKYBuffer_GetShortLE(const CKYBuffer *buf, CKYOffset offset)
{
    unsigned short val;
    if (buf->len < offset+2) {
	return 0;
    }
    val  = ((unsigned short)buf->data[offset+1]) << 8;
    val |= ((unsigned short)buf->data[offset+0]) << 0;
    return val;
}
