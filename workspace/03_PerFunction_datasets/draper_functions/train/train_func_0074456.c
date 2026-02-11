guard_region ( void *region, size_t len ) {
	uint32_t offset = 0;

	len &= ~0x03;
	for ( offset = 0; offset < len ; offset += 4 ) {
		*((uint32_t *)(region + offset)) = GUARD_SYMBOL;
	}
}
