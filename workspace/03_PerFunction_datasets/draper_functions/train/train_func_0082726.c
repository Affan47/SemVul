chksum_getresult(chksum_t *ct, const header_t *h)
{
	return (h->flags & F_H_CRC32) ? ct->f_crc32 : ct->f_adler32;
}
