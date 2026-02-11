next_ebr_part(struct disk_part_iter *part)
{
    const struct part_entry *ebr_table;
    const struct part_entry *parent_table =
	((const struct mbr *)part->private.ebr.parent->block)->table;
    static const struct part_entry phony = {.start_lba = 0 };
    uint64_t ebr_lba;


    if (part->private.ebr.parent_index >= 0)

	ebr_table = ((const struct mbr *)part->block)->table + 1;

    if (part->private.ebr.parent_index < 0 || !ebr_table->start_lba) {

	while (++part->private.ebr.parent_index < 4) {
	    uint8_t type = parent_table[part->private.ebr.parent_index].ostype;

	    if ((type == 0x05) || (type == 0x0F) || (type == 0x85))
		break;
	}
	if (part->private.ebr.parent_index == 4)

	    goto out_finished;
	part->private.ebr.lba_extended =
	    parent_table[part->private.ebr.parent_index].start_lba;
	ebr_table = &phony;
    }

    ebr_lba = ebr_table->start_lba + part->private.ebr.lba_extended;
    free(part->block);
    part->block = read_sectors(ebr_lba, 1);
    if (!part->block) {
	error("Could not load EBR!\n");
	goto err_ebr;
    }
    ebr_table = ((const struct mbr *)part->block)->table;
    dprintf("next_ebr_part:\n");
    mbr_part_dump(ebr_table);


    {
	const struct mbr *mbr =
	    (const struct mbr *)part->private.ebr.parent->block;
	const struct part_entry *extended =
	    mbr->table + part->private.ebr.parent_index;

	if (ebr_table[0].start_lba >= extended->start_lba + extended->length) {
	    dprintf("Insane logical partition!\n");
	    goto err_insane;
	}
    }

    part->lba_data = ebr_table[0].start_lba + ebr_lba;
    dprintf("Partition %d logical lba %"PRIu64"\n",
	    part->index, part->lba_data);
    part->index++;
    part->record = ebr_table;
    return part;

err_insane:

    free(part->block);
    part->block = NULL;
err_ebr:

out_finished:
    free(part->private.ebr.parent->block);
    free(part->private.ebr.parent);
    free(part->block);
    free(part);
    return NULL;
}
