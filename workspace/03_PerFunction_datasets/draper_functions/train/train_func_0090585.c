cfg_partition_find_by_name_or_num(int fd, const char *partnamestr, int part_num,
		Disk *dsk)
{
	Cfg_dirent *direntptr;
	int	match;
	int	num_parts;
	int	i;

	num_parts = cfg_partition_make_list(fd);

	if(num_parts <= 0) {
		return -1;
	}

	for(i = 0; i < g_cfg_partitionlist.last; i++) {
		direntptr = &(g_cfg_partitionlist.direntptr[i]);
		match = 0;
		if((strncmp(partnamestr, direntptr->name, 32) == 0) &&
							(part_num < 0)) {


			match = 1;
		}
		if((partnamestr == 0) && (direntptr->part_num == part_num)) {


			match = 1;
		}
		if(match) {
			dsk->image_start = direntptr->image_start;
			dsk->image_size = direntptr->size;


			return i;
		}
	}

	return -1;
}
