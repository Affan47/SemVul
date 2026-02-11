dump_memory_banks(struct s_hardware *hardware, ZZJSON_CONFIG *config, ZZJSON **item) {

	if (hardware->dmi.memory_count == 0) {
			CREATE_NEW_OBJECT;
				add_s("dmi.warning","No memory bank structure found");
			FLUSH_OBJECT;
			return;
	}

	for (int bank=0; bank<hardware->dmi.memory_count;bank++) {

		if (hardware->dmi.memory[bank].filled == false) {
			char msg[64]={0};
			snprintf(msg,sizeof(msg),"Bank %d doesn't contain any information", bank);

			CREATE_NEW_OBJECT;
				add_s("dmi.warning",msg);
			FLUSH_OBJECT;
			continue;
		}

		CREATE_NEW_OBJECT;
		add_i("Memory Bank", bank);
		add_s("dmi.memory.form_factor", hardware->dmi.memory[bank].form_factor);
		add_s("dmi.memory.type", hardware->dmi.memory[bank].type);
		add_s("dmi.memory.type_detail", hardware->dmi.memory[bank].type_detail);
		add_s("dmi.memory.speed", hardware->dmi.memory[bank].speed);
		add_s("dmi.memory.size", hardware->dmi.memory[bank].size);
		add_s("dmi.memory.device_set", hardware->dmi.memory[bank].device_set);
		add_s("dmi.memory.device_locator", hardware->dmi.memory[bank].device_locator);
		add_s("dmi.memory.bank_locator", hardware->dmi.memory[bank].bank_locator);
		add_s("dmi.memory.total_width", hardware->dmi.memory[bank].total_width);
		add_s("dmi.memory.data_width", hardware->dmi.memory[bank].data_width);
		add_s("dmi.memory.error", hardware->dmi.memory[bank].error);
		add_s("dmi.memory.vendor", hardware->dmi.memory[bank].manufacturer);
		add_s("dmi.memory.serial", hardware->dmi.memory[bank].serial);
		add_s("dmi.memory.asset_tag", hardware->dmi.memory[bank].asset_tag);
		add_s("dmi.memory.part_number", hardware->dmi.memory[bank].part_number);
		FLUSH_OBJECT;
	}
}
