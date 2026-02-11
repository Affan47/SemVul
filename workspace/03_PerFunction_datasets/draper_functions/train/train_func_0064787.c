set_kvm_iohole(char *optarg)
{
#define DEFAULT_IOHOLE() \
	((kvm->mapinfo.cpu_version_id <= 9) ? 0x40000000 : 0x20000000)
#define E820_RAM 1

	if (optarg) {
		ulong flags;
		ulonglong iohole;
		char *arg;

		flags = LONG_LONG;
		if (IS_A_NUMBER(&LASTCHAR(optarg)))
			flags |= HEX_BIAS;

		arg = strdup(optarg);

		if (!calculate(arg, NULL, &iohole, flags))
			error(FATAL,
			    "invalid --kvm_iohole argument: %s\n", optarg);

		free(arg);


		if ((iohole != 0x20000000ULL) && (iohole != 0x40000000ULL))
			error(WARNING, "questionable --kvmio argument: %s\n",
				optarg);

		kvm->iohole = iohole;

	} else {
	        int nr_map, i;
	        char *buf, *e820entry;
	        ulonglong addr, size, ending_addr;
	        uint type;

		if (kvm->iohole)
			return;

		kvm->iohole = DEFAULT_IOHOLE();

		if (!symbol_exists("e820"))
			return;

	        buf = (char *)GETBUF(SIZE(e820map));
	        if (!readmem(symbol_value("e820"), KVADDR, &buf[0],
		    SIZE(e820map), "e820map", RETURN_ON_ERROR|QUIET)) {
			FREEBUF(buf);
			return;
		}

		nr_map = INT(buf + OFFSET(e820map_nr_map));

		for (i = 0; i < nr_map; i++) {
                	e820entry = buf + sizeof(int) + (SIZE(e820entry) * i);
                	addr = ULONGLONG(e820entry + OFFSET(e820entry_addr));
			size = ULONGLONG(e820entry + OFFSET(e820entry_size));
                	type = UINT(e820entry + OFFSET(e820entry_type));

			if (type != E820_RAM)
				continue;
			if (addr >= 0x100000000ULL)
				break;

			ending_addr = addr + size;
			if ((ending_addr > 0xc0000000ULL) &&
			    (ending_addr <= 0xe0000000ULL)) {
				kvm->iohole = 0x20000000ULL;
				break;
			}
        	}

		FREEBUF(buf);
	}
}
