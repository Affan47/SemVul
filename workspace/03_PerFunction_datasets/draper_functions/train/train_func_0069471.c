read32le(uint32 *Bufo, EMUFILE *fp)
{
	uint32 buf;
	if(fp->_fread(&buf,4)<4)
		return 0;
#ifdef LOCAL_LE
	*(u32*)Bufo=buf;
#else
	*(u32*)Bufo=((buf&0xFF)<<24)|((buf&0xFF00)<<8)|((buf&0xFF0000)>>8)|((buf&0xFF000000)>>24);
#endif
	return 1;
}
