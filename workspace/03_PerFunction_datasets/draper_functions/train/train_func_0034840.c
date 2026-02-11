print_flags(long flags)
{
	if (flags & IFF_TUN)
		printf(" tun");

	if (flags & IFF_TAP)
		printf(" tap");

	if (!(flags & IFF_NO_PI))
		printf(" pi");

	if (flags & IFF_ONE_QUEUE)
		printf(" one_queue");

	if (flags & IFF_VNET_HDR)
		printf(" vnet_hdr");

	flags &= ~(IFF_TUN|IFF_TAP|IFF_NO_PI|IFF_ONE_QUEUE|IFF_VNET_HDR);
	if (flags)
		printf(" UNKNOWN_FLAGS:%lx", flags);
}
