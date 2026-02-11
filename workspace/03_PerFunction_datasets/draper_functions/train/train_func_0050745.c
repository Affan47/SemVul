flashAddress(uint32_t startAddr, uint32_t *data, uint32_t len) {
	FLASH_Status status;
	int retries;
	int ret = 1;
	int i;

	FLASH_Unlock();


	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	for (i = 0; i < len; i++) {
		retries = 0;
		do {
			status = FLASH_ProgramWord(startAddr + i*4, *(data + i));
			retries++;
		} while (status != FLASH_COMPLETE && retries < FLASH_RETRIES);

		if (retries == FLASH_RETRIES) {
			ret = 0;
			break;
		}
	}

	FLASH_Lock();

	return ret;
}
