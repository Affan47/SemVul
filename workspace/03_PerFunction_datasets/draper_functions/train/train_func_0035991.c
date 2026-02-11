bc_get_astore_index(const unsigned char *code)
{
	if (*code == OPC_WIDE)
		return read_u16(code + 2);

	switch (*code) {
	case OPC_ASTORE:
		return read_u8(code + 1);
	case OPC_ASTORE_0:
		return 0;
	case OPC_ASTORE_1:
		return 1;
	case OPC_ASTORE_2:
		return 2;
	case OPC_ASTORE_3:
		return 3;
	default:
		assert(!"not an astore instruction");
	}
}
