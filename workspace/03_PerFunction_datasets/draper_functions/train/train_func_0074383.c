add_disk_randomness(struct gendisk *disk)
{
	if (!disk || !disk->random)
		return;

	add_timer_randomness(disk->random, 0x100 + disk_devt(disk));
	trace_add_disk_randomness(disk_devt(disk), ENTROPY_BITS(&input_pool));
}
