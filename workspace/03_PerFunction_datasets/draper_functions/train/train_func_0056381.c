dump_unmanaged_coderefs (MonoProfiler *prof)
{
	int i;
	const char* last_symbol;
	uintptr_t addr, page_end;

	if (load_binaries (prof))
		return;
	for (i = 0; i < size_code_pages; ++i) {
		const char* sym;
		if (!code_pages [i] || code_pages [i] & 1)
			continue;
		last_symbol = NULL;
		addr = CPAGE_ADDR (code_pages [i]);
		page_end = addr + CPAGE_SIZE;
		code_pages [i] |= 1;

		for (; addr < page_end; addr += 16) {
			sym = symbol_for (addr);
			if (sym && sym == last_symbol)
				continue;
			last_symbol = sym;
			if (!sym)
				continue;
			dump_usym (sym, addr, 0);

		}
	}
}
