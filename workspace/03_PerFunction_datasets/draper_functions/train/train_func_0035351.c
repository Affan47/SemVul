bcma_sprom_valid(struct bcma_bus *bus, const u16 *sprom,
			    size_t words)
{
	u16 revision;
	int err;

	err = bcma_sprom_check_crc(sprom, words);
	if (err)
		return err;

	revision = sprom[words - 1] & SSB_SPROM_REVISION_REV;
	if (revision != 8 && revision != 9 && revision != 10) {
		pr_err("Unsupported SPROM revision: %d\n", revision);
		return -ENOENT;
	}

	bus->sprom.revision = revision;
	bcma_debug(bus, "Found SPROM revision %d\n", revision);

	return 0;
}
