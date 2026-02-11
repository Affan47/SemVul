rfc3484_compare(const void *__one, const void *__two)
{
	const struct sort_result *one = __one;
	const struct sort_result *two = __two;


	if (one->reachable && !two->reachable)
		return -1;
	else if (two->reachable && !one->reachable)
		return 1;


	if (one->dst_scope == one->src_scope &&
				two->dst_scope != two->src_scope)
		return -1;
	else if (two->dst_scope == two->src_scope &&
				one->dst_scope != one->src_scope)
		return 1;


	if (one->dst_label == one->src_label &&
				two->dst_label != two->src_label)
		return -1;
	else if (two->dst_label == two->src_label &&
				one->dst_label != one->src_label)
		return 1;


	if (one->precedence > two->precedence)
		return -1;
	else if (two->precedence > one->precedence)
		return 1;


	if (one->dst_scope != two->dst_scope)
		return one->dst_scope - two->dst_scope;


	if (one->dst.sa.sa_family == AF_INET) {


	} else {
		int i;

		for (i = 0; i < 4; i++) {
			guint32 cmp_one, cmp_two;

			cmp_one = one->src.sin6.sin6_addr.s6_addr32[i] ^
					one->dst.sin6.sin6_addr.s6_addr32[i];
			cmp_two = two->src.sin6.sin6_addr.s6_addr32[i] ^
					two->dst.sin6.sin6_addr.s6_addr32[i];

			if (!cmp_two && !cmp_one)
				continue;

			if (cmp_one && !cmp_two)
				return 1;
			if (cmp_two && !cmp_one)
				return -1;


			cmp_one = g_bit_storage(ntohl(cmp_one));
			cmp_two = g_bit_storage(ntohl(cmp_two));

			if (cmp_one == cmp_two)
				break;

			return cmp_one - cmp_two;
		}
	}


	if (one < two)
		return -1;
	else
		return 1;
}
