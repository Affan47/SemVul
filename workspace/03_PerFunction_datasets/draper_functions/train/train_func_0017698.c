sadump_get_smram_cpu_state(int apicid,
			   struct sadump_smram_cpu_state *smram)
{
	ulong offset;

	if (!sd->sub_hdr_offset || !sd->smram_cpu_state_size ||
	    apicid >= sd->dump_header->nr_cpus)
		return FALSE;

	offset = sd->sub_hdr_offset + sizeof(uint32_t) +
		sd->dump_header->nr_cpus * sizeof(struct sadump_apic_state);

	if (lseek(sd->dfd, offset + apicid * sd->smram_cpu_state_size,
		  SEEK_SET) == failed)
		error(FATAL,
		      "sadump: cannot lseek smram cpu state in dump sub header\n");

	if (read(sd->dfd, smram, sd->smram_cpu_state_size) != sd->smram_cpu_state_size)
		error(FATAL, "sadump: cannot read smram cpu state in dump sub "
		      "header\n");

	return TRUE;
}
