print_types(uint16_t types, int inverted, int numeric)
{
	int have_type = 0;

	if (inverted)
		printf(" !");

	printf(" ");
	while (types) {
		unsigned int i;

		for (i = 0; !(types & (1 << i)); i++);

		if (have_type)
			printf(",");
		else
			have_type = 1;

		if (numeric)
			printf("%u", i);
		else
			printf("%s", dccp_pkt_types[i]);

		types &= ~(1 << i);
	}
}
