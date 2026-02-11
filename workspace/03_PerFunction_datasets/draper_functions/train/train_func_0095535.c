detect_bios_type(vbios_map * map, int entry_size)
{
    unsigned int i;
    uint16_t r1, r2;

    r1 = r2 = 32000;

    for (i = 0; i < map->mode_table_size; i++) {
        if (map->mode_table[i].resolution <= r1) {
            r1 = map->mode_table[i].resolution;
    	} else if (map->mode_table[i].resolution <= r2) {
	    r2 = map->mode_table[i].resolution;
    	}
    }

    return ((r2-r1-6) % entry_size) == 0;
}
