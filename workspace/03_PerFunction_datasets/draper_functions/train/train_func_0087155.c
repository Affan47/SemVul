sample_src_names(unsigned int use)
{
	int bit;

	trash.len = 0;
	trash.str[0] = '\0';
	for (bit = 0; bit < SMP_SRC_ENTRIES; bit++) {
		if (!(use & ~((1 << bit) - 1)))
			break;

		if (!(use & (1 << bit)))
			continue;

		trash.len += snprintf(trash.str + trash.len, trash.size - trash.len, "%s%s",
				      (use & ((1 << bit) - 1)) ? "," : "",
		                      fetch_src_names[bit]);
	}
	return trash.str;
}
