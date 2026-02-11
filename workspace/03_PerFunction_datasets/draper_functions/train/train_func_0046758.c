pmc_dev_state_print(struct seq_file *s, int reg_index,
				u32 sts, const struct pmc_bit_map *sts_map,
				u32 fd, const struct pmc_bit_map *fd_map)
{
	int offset = PMC_REG_BIT_WIDTH * reg_index;
	int index;

	for (index = 0; sts_map[index].name; index++) {
		seq_printf(s, "Dev: %-2d - %-32s\tState: %s [%s]\n",
			offset + index, sts_map[index].name,
			fd_map[index].bit_mask & fd ?  "Disabled" : "Enabled ",
			sts_map[index].bit_mask & sts ?  "D3" : "D0");
	}
}
