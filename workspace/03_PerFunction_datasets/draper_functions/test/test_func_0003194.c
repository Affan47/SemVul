free_main(int argc UNUSED_PARAM, char **argv IF_NOT_DESKTOP(UNUSED_PARAM))
{
	struct sysinfo info;

	INIT_G();

#if ENABLE_DESKTOP
	G.unit_steps = 10;
	if (argv[1] && argv[1][0] == '-') {
		switch (argv[1][1]) {
		case 'b':
			G.unit_steps = 0;
			break;
		case 'k':

			break;
		case 'm':
			G.unit_steps = 20;
			break;
		case 'g':
			G.unit_steps = 30;
			break;
		default:
			bb_show_usage();
		}
	}
#endif

	sysinfo(&info);


	G.mem_unit = (info.mem_unit ? info.mem_unit : 1);

	printf("     %13s%13s%13s%13s%13s\n",
		"total",
		"used",
		"free",
		"shared", "buffers"


	);

#define FIELDS_5 "%13llu%13llu%13llu%13llu%13llu\n"
#define FIELDS_3 (FIELDS_5 + 2*6)
#define FIELDS_2 (FIELDS_5 + 3*6)

	printf("Mem: ");
	printf(FIELDS_5,
		scale(info.totalram),
		scale(info.totalram - info.freeram),
		scale(info.freeram),
		scale(info.sharedram),
		scale(info.bufferram)
	);


	printf("-/+ buffers:      ");
	printf(FIELDS_2,
		scale(info.totalram - info.freeram - info.bufferram),
		scale(info.freeram + info.bufferram)
	);
#if BB_MMU
	printf("Swap:");
	printf(FIELDS_3,
		scale(info.totalswap),
		scale(info.totalswap - info.freeswap),
		scale(info.freeswap)
	);
#endif
	return EXIT_SUCCESS;
}
