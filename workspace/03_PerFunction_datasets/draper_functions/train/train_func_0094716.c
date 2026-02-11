show_dmi_memory_modules(int argc __unused, char **argv __unused,
			     struct s_hardware *hardware)
{

    int show_free_banks = 1;

    more_printf("Memory Size   : %lu MB (%lu KB)\n",
		(hardware->detected_memory_size + (1 << 9)) >> 10,
		hardware->detected_memory_size);

    if ((hardware->dmi.memory_count <= 0)
	&& (hardware->dmi.memory_module_count <= 0)) {
	more_printf("No memory bank found\n");
	return;
    }


    if (argc > 0) {


	show_free_banks = strtol(argv[0], NULL, 10);
	if (errno == ERANGE || show_free_banks < 0 || show_free_banks > 1)
	    goto usage;
    }

    reset_more_printf();

    if (hardware->dmi.memory_count > 0) {
	char bank_number[255];
	more_printf("Memory Banks\n");
	for (int i = 0; i < hardware->dmi.memory_count; i++) {
	    if (hardware->dmi.memory[i].filled == true) {
		memset(bank_number, 0, sizeof(bank_number));
		snprintf(bank_number, sizeof(bank_number), "%d ", i);
		if (show_free_banks == false) {
		    if (strncmp(hardware->dmi.memory[i].size, "Free", 4))
			more_printf(" bank %02d      : %s %s@%s\n",
				    i, hardware->dmi.memory[i].size,
				    hardware->dmi.memory[i].type,
				    hardware->dmi.memory[i].speed);
		} else {
		    more_printf(" bank %02d      : %s %s@%s\n", i,
				hardware->dmi.memory[i].size,
				hardware->dmi.memory[i].type,
				hardware->dmi.memory[i].speed);
		}
	    }
	}
    } else if (hardware->dmi.memory_module_count > 0) {

	more_printf("Memory Modules\n");
	for (int i = 0; i < hardware->dmi.memory_module_count; i++) {
	    if (hardware->dmi.memory_module[i].filled == true) {
		more_printf(" module %02d    : %s %s@%s\n", i,
			    hardware->dmi.memory_module[i].enabled_size,
			    hardware->dmi.memory_module[i].type,
			    hardware->dmi.memory_module[i].speed);
	    }
	}
    }

    return;


usage:
    more_printf("show memory <clear screen? <show free banks?>>\n");
    return;
}
