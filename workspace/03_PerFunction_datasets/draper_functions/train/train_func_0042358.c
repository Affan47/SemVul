cl_uuid_g_hash(gconstpointer uuid_ptr)
{
	guint			ret = 0U;
	guint32			value32;
	int			index;
	const unsigned char *	uuid_char = uuid_ptr;


	for (index = 0; index < sizeof(cl_uuid_t); index += sizeof(value32)) {
		memcpy(&value32, uuid_char+index, sizeof (value32));
		ret += g_ntohl(value32);
	}
	return ret;
}
