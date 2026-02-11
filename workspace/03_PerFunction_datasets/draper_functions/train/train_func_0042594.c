convert_icmptype_specifier(struct icmptype_specifier_s * n) {
    struct filter * res = NULL;

    eprint("converting icmptype specifier\n");

    if (n->list) {
	res = new_filter_sibs(convert_icmptype_argument_list(n->list));
    } else {
	printf("error: no icmptype argument list\n");
    }

    return res;
}
