check_start_after_end_paritions(struct gpt_header *header,
						struct gpt_entry *ents)
{
	uint32_t i;

	for (i = 0; i < le32_to_cpu(header->npartition_entries); i++) {
		if (partition_unused(&ents[i]))
			continue;
		if (gpt_partition_start(&ents[i]) > gpt_partition_end(&ents[i]))
			return i + 1;
	}

	return 0;
}
