kirk_CMD4(u8* outbuff, u8* inbuff, int size)
{
	KIRK_AES128CBC_HEADER *header = (KIRK_AES128CBC_HEADER*)inbuff;
	u8* key;
	AES_ctx aesKey;

	if (is_kirk_initialized == 0) return KIRK_NOT_INITIALIZED;
	if (header->mode != KIRK_MODE_ENCRYPT_CBC) return KIRK_INVALID_MODE;
	if (header->data_size == 0) return KIRK_DATA_SIZE_ZERO;

	key = kirk_4_7_get_key(header->keyseed);
	if (key == (u8*)KIRK_INVALID_SIZE) return KIRK_INVALID_SIZE;


	AES_set_key(&aesKey, key, 128);
	AES_cbc_encrypt(&aesKey, inbuff+sizeof(KIRK_AES128CBC_HEADER), outbuff+sizeof(KIRK_AES128CBC_HEADER), size);

	return KIRK_OPERATION_SUCCESS;
}
