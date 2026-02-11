vmsg_fill_header(gnutella_header_t *header, uint32 size, uint32 maxsize)
{
	uint32 msize;


	gnutella_header_set_muid(header, &blank_guid);
	gnutella_header_set_function(header, GTA_MSG_VENDOR);
	gnutella_header_set_ttl(header, 1);
	gnutella_header_set_hops(header, 0);

	msize = size + sizeof(gnutella_vendor_t);

	gnutella_header_set_size(header, msize);

	msize += GTA_HEADER_SIZE;

	if (msize > maxsize)
		g_error("allocated vendor message is only %u bytes, would need %u",
			maxsize, msize);

	return msize;
}
