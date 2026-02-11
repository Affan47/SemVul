cpumask_parse(const char *str, cpu_set_t *set, size_t setsize)
{
	int len = strlen(str);
	const char *ptr = str + len - 1;
	int cpu = 0;


	if (len > 1 && !memcmp(str, "0x", 2L))
		str += 2;

	CPU_ZERO_S(setsize, set);

	while (ptr >= str) {
		char val;


		if (*ptr == ',')
			ptr--;

		val = char_to_val(*ptr);
		if (val == (char) -1)
			return -1;
		if (val & 1)
			CPU_SET_S(cpu, setsize, set);
		if (val & 2)
			CPU_SET_S(cpu + 1, setsize, set);
		if (val & 4)
			CPU_SET_S(cpu + 2, setsize, set);
		if (val & 8)
			CPU_SET_S(cpu + 3, setsize, set);
		len--;
		ptr--;
		cpu += 4;
	}

	return 0;
}
