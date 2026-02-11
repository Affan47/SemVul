nbl_decompress_get_next_control_bit(nbl_decompress_struct* p)
{
	unsigned char ret;

	p->uControlByteCounter--;
	if (p->uControlByteCounter == 0) {
		p->ucControlByte = p->pstrSrc[p->iSrcPos++];
		p->uControlByteCounter = 8;
	}

	ret = p->ucControlByte & 0x1;
	p->ucControlByte >>= 1;

	return ret;
}
