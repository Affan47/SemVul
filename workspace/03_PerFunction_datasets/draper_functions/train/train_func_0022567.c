af_make_gid(AFFILE *af)
{
    int ret = 0;
    AF_WRLOCK(af);
    if(af_get_seg(af,AF_IMAGE_GID,0,0,0)!=0){
	unsigned char bit128[16];
	RAND_pseudo_bytes(bit128,sizeof(bit128));
	int r = af_update_seg(af,AF_IMAGE_GID,0,bit128,sizeof(bit128));
	if(r<0) ret = -1;
	else ret = 1;
    }
    AF_UNLOCK(af);
    return ret;
}
