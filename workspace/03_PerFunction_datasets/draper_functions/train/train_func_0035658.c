ginsm(H *hdr, unsigned char *ptr, int ofst, unsigned char *blk, int size)
{
	if (ofst != hdr->hole)
		gstgap(hdr, ptr, ofst);
	mmove(ptr + hdr->hole, blk, size);
	hdr->hole += size;
	vchanged(ptr);
}
