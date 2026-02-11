DISK_update_adkcon (int hpos, uae_u16 v)
{
	uae_u16 vold = adkcon;
	uae_u16 vnew = adkcon;
	if (v & 0x8000)
		 vnew |= v & 0x7FFF;
	else
		vnew &= ~v;
	if ((vnew & 0x400) && !(vold & 0x400))
		bitoffset = 0;
}
