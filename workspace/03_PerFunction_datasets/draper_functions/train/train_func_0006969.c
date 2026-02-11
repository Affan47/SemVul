write_header(FILE *file, dns_rbt_t *rbt, isc_uint64_t first_node_offset,
	     isc_uint64_t crc)
{
	file_header_t header;
	isc_result_t result;
	off_t location;

	if (FILE_VERSION[0] == '\0') {
		memset(FILE_VERSION, 0, sizeof(FILE_VERSION));
		snprintf(FILE_VERSION, sizeof(FILE_VERSION),
			 "RBT Image %s %s", dns_major, dns_mapapi);
	}

	memset(&header, 0, sizeof(file_header_t));
	memmove(header.version1, FILE_VERSION, sizeof(header.version1));
	memmove(header.version2, FILE_VERSION, sizeof(header.version2));
	header.first_node_offset = first_node_offset;
	header.ptrsize = (isc_uint32_t) sizeof(void *);
	header.bigendian = (1 == htonl(1)) ? 1 : 0;

#ifdef DNS_RDATASET_FIXED
	header.rdataset_fixed = 1;
#else
	header.rdataset_fixed = 0;
#endif

	header.nodecount = rbt->nodecount;

	header.crc = crc;

	CHECK(isc_stdio_tell(file, &location));
	location = dns_rbt_serialize_align(location);
	CHECK(isc_stdio_seek(file, location, SEEK_SET));
	CHECK(isc_stdio_write(&header, 1, sizeof(file_header_t), file, NULL));
	CHECK(fflush(file));


	CHECK(isc_stdio_seek(file, 0, SEEK_END));

 cleanup:
	return (result);
}
