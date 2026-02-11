_af_compression_unit_from_id (int compressionid)
{
	for (int i=0; i<_AF_NUM_COMPRESSION; i++)
		if (_af_compression[i].compressionID == compressionid)
			return &_af_compression[i];

	_af_error(AF_BAD_COMPTYPE, "compression type %d not available", compressionid);
	return NULL;
}
