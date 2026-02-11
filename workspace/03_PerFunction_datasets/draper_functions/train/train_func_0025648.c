rbug_demarshal_texture_read(struct rbug_proto_header *header)
{
	uint32_t len = 0;
	uint32_t pos = 0;
	uint8_t *data =  NULL;
	struct rbug_proto_texture_read *ret;

	if (!header)
		return NULL;
	if (header->opcode != (int32_t)RBUG_OP_TEXTURE_READ)
		return NULL;

	pos = 0;
	len = header->length * 4;
	data = (uint8_t*)&header[1];
	ret = MALLOC(sizeof(*ret));
	if (!ret)
		return NULL;

	ret->header.__message = header;
	ret->header.opcode = header->opcode;

	READ(8, rbug_texture_t, texture);
	READ(4, uint32_t, face);
	READ(4, uint32_t, level);
	READ(4, uint32_t, zslice);
	READ(4, uint32_t, x);
	READ(4, uint32_t, y);
	READ(4, uint32_t, w);
	READ(4, uint32_t, h);

	return ret;
}
