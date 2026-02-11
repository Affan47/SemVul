CKYBuffer_AppendChar(CKYBuffer *buf, CKYByte val)
{
    CKYStatus ret;

    ret = CKYBuffer_Reserve(buf, buf->len + 1);
    if (ret != CKYSUCCESS) {
	return ret;
    }
    buf->data[buf->len] = val;
    buf->len += 1;
    return CKYSUCCESS;
}
