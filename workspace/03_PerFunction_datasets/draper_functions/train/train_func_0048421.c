LoadInterface(u32 InterfaceType)
{
	switch (InterfaceType) {
#ifndef GPAC_DISABLE_MPEG2TS
	case GF_NET_CLIENT_INTERFACE: return (GF_BaseInterface *) NewM2TSReader();
#endif
	default: return NULL;
	}
}
