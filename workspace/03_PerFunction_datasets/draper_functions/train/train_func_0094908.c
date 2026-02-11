convert_family (MonoAddressFamily mono_family)
{
	switch (mono_family) {
	case AddressFamily_Unknown:
	case AddressFamily_ImpLink:
	case AddressFamily_Pup:
	case AddressFamily_Chaos:
	case AddressFamily_Iso:
	case AddressFamily_Ecma:
	case AddressFamily_DataKit:
	case AddressFamily_Ccitt:
	case AddressFamily_DataLink:
	case AddressFamily_Lat:
	case AddressFamily_HyperChannel:
	case AddressFamily_NetBios:
	case AddressFamily_VoiceView:
	case AddressFamily_FireFox:
	case AddressFamily_Banyan:
	case AddressFamily_Atm:
	case AddressFamily_Cluster:
	case AddressFamily_Ieee12844:
	case AddressFamily_NetworkDesigners:
		g_warning("System.Net.Sockets.AddressFamily has unsupported value 0x%x", mono_family);
		return -1;
	case AddressFamily_Unspecified:
		return AF_UNSPEC;
	case AddressFamily_Unix:
		return AF_UNIX;
	case AddressFamily_InterNetwork:
		return AF_INET;
	case AddressFamily_AppleTalk:
		return AF_APPLETALK;
	case AddressFamily_InterNetworkV6:
		return AF_INET6;
	case AddressFamily_DecNet:
#ifdef AF_DECnet
		return AF_DECnet;
#else
		return -1;
#endif
	case AddressFamily_Ipx:
#ifdef AF_IPX
		return AF_IPX;
#else
		return -1;
#endif
	case AddressFamily_Sna:
#ifdef AF_SNA
		return AF_SNA;
#else
		return -1;
#endif
	case AddressFamily_Irda:
#ifdef AF_IRDA
		return AF_IRDA;
#else
		return -1;
#endif
	default:
		g_warning ("System.Net.Sockets.AddressFamily has unknown value 0x%x", mono_family);
		return -1;
	}
}
