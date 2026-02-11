zAddDNACompanion(zDNA* dna, const char* key, void* ptr) {
	void* old = NULL;
	if ((old = zGetHash(dna->companion, key)) != NULL) {
		zFree(old);
	}
	zSetHash(dna->companion, key, ptr);
}
