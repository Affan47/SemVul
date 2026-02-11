show_partition_information(struct driveinfo *drive_info,
				       struct part_entry *ptab,
				       int partition_offset,
				       int nb_partitions_seen)
{
    char size[11];
    char bootloader_name[9];
    char *parttype;
    unsigned int start, end;

    int i = nb_partitions_seen;

    reset_more_printf();

    start = partition_offset;
    end = start + ptab->length - 1;

    if (ptab->length > 0)
	sectors_to_size(ptab->length, size);
    else
	memset(size, 0, sizeof size);

    if (i == 1)
	more_printf(" #  B       Start         End    Size Id Type\n");

    get_label(ptab->ostype, &parttype);
    more_printf("%2d  %s %11d %11d %s %02X %s",
		i, (ptab->active_flag == 0x80) ? "x" : " ",
		start, end, size, ptab->ostype, parttype);


    if (ptab->ostype == 0x82 && swsusp_check(drive_info, ptab))
	more_printf("%s", " (Swsusp sig. detected)");

    if (get_bootloader_string(drive_info, ptab, bootloader_name, 9) == 0)
	more_printf("%-46s %s %s", " ", "Bootloader:", bootloader_name);

    more_printf("\n");

    free(parttype);
}
