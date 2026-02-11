StateRestore(int version) {
	if (bbrk & 2) {
		FixMMC3PRG(MMC3_cmd);
		FixMMC3CHR(MMC3_cmd);
	} else
		Sync();
}
