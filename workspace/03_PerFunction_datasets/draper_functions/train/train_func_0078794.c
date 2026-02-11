fdt_translate_one(const void *blob, int parent,
				    const struct of_bus *bus,
				    const struct of_bus *pbus, __be32 *addr,
				    int na, int ns, int pna, const char *rprop)
{
	const __be32 *ranges;
	int rlen;
	int rone;
	u64 offset = OF_BAD_ADDR;

	ranges = fdt_getprop(blob, parent, rprop, &rlen);
	if (!ranges)
		return 1;
	if (rlen == 0) {
		offset = of_read_number(addr, na);
		memset(addr, 0, pna * 4);
		pr_debug("FDT: empty ranges, 1:1 translation\n");
		goto finish;
	}

	pr_debug("FDT: walking ranges...\n");


	rlen /= 4;
	rone = na + pna + ns;
	for (; rlen >= rone; rlen -= rone, ranges += rone) {
		offset = bus->map(addr, ranges, na, ns, pna);
		if (offset != OF_BAD_ADDR)
			break;
	}
	if (offset == OF_BAD_ADDR) {
		pr_debug("FDT: not found !\n");
		return 1;
	}
	memcpy(addr, ranges + na, 4 * pna);

 finish:
	of_dump_addr("FDT: parent translation for:", addr, pna);
	pr_debug("FDT: with offset: %llx\n", offset);


	return pbus->translate(addr, offset, pna);
}
