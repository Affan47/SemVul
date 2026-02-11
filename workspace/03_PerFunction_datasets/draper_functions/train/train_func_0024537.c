readItem(PRFileDesc *fd, SECItem *item)
{
    unsigned char buf[4];
    int bytesRead;


    bytesRead = PR_Read(fd, buf, 4);
    if (bytesRead != 4) {
	return SECFailure;
    }
    item->len = decodeInt(buf);

    item->data = PORT_Alloc(item->len);
    if (item->data == NULL) {
	item->len = 0;
	return SECFailure;
    }
    bytesRead = PR_Read(fd, item->data, item->len);
    if (bytesRead != item->len) {
	PORT_Free(item->data);
	item->data = NULL;
	item->len = 0;
	return SECFailure;
    }
    return SECSuccess;
}
