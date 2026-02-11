ast_cdr_setdisposition(struct ast_cdr *cdr, long int disposition)
{

	for (; cdr; cdr = cdr->next) {
		if (ast_test_flag(cdr, AST_CDR_FLAG_LOCKED))
			continue;
		check_post(cdr);
		cdr->disposition = disposition;
	}
}
