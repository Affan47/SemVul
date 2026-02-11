_build_all_partitionline_info(void)
{
	slurm_conf_partition_t **ptr_array;
	int count;
	int i;

	count = slurm_conf_partition_array(&ptr_array);
	if (count == 0)
		fatal("No PartitionName information available!");

	for (i = 0; i < count; i++)
		_build_single_partitionline_info(ptr_array[i]);

	return SLURM_SUCCESS;
}
