cmmf_copy_secitem (PLArenaPool *poolp, SECItem *dest, SECItem *src)
{
    SECStatus rv;

    if (src->data != NULL) {
        rv = SECITEM_CopyItem(poolp, dest, src);
    } else {
        dest->data = NULL;
	dest->len  = 0;
	rv = SECSuccess;
    }
    return rv;
}
