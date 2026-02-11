print_icmp_type(uint8_t *type, uint8_t *code)
{
	unsigned int i;

	if (type[0] != type[1]) {
		printf("%"PRIu8 ":%" PRIu8, type[0], type[1]);
		print_icmp_code(code);
		return;
	}

	for (i = 0; i < ARRAY_SIZE(icmpv6_codes); i++) {
		if (icmpv6_codes[i].type != type[0])
			continue;

		if (icmpv6_codes[i].code_min == code[0] &&
		    icmpv6_codes[i].code_max == code[1]) {
			printf("%s ", icmpv6_codes[i].name);
			return;
		}
	}
	printf("%"PRIu8, type[0]);
	print_icmp_code(code);
}
