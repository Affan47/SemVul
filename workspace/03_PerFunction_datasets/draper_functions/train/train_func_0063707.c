getcolorv(palette *pal, uint index)
{
	if ((index<pal->size) && (pal->data)) return pal->data[index];
	return VCP(VC_WHITE, VC_RED);
}
