fdisk_partition_has_partno(struct fdisk_partition *pa)
{
	return pa && !FDISK_IS_UNDEF(pa->partno);
}
