make_condition_modifier(struct iforce* iforce,
	struct resource* mod_chunk, int no_alloc,
	__u16 rsat, __u16 lsat, __s16 rk, __s16 lk, u16 db, __s16 center)
{
	unsigned char data[10];

	if (!no_alloc) {
		mutex_lock(&iforce->mem_mutex);
		if (allocate_resource(&(iforce->device_memory), mod_chunk, 8,
			iforce->device_memory.start, iforce->device_memory.end, 2L,
			NULL, NULL)) {
			mutex_unlock(&iforce->mem_mutex);
			return -ENOSPC;
		}
		mutex_unlock(&iforce->mem_mutex);
	}

	data[0] = LO(mod_chunk->start);
	data[1] = HI(mod_chunk->start);

	data[2] = (100 * rk) >> 15;
	data[3] = (100 * lk) >> 15;

	center = (500 * center) >> 15;
	data[4] = LO(center);
	data[5] = HI(center);

	db = (1000 * db) >> 16;
	data[6] = LO(db);
	data[7] = HI(db);

	data[8] = (100 * rsat) >> 16;
	data[9] = (100 * lsat) >> 16;

	iforce_send_packet(iforce, FF_CMD_CONDITION, data);
	iforce_dump_packet("condition", FF_CMD_CONDITION, data);

	return 0;
}
