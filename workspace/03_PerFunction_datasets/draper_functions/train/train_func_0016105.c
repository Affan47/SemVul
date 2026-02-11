upload_new_stalling(const struct upload *u)
{
	if (GNET_PROPERTY(upload_debug)) {
		g_debug("UL request #%u to %s (%s) stalled after %s bytes sent",
			u->reqnum, host_addr_to_string(u->addr), upload_vendor_str(u),
			uint64_to_string(u->sent));
	}

	upload_stall();
}
