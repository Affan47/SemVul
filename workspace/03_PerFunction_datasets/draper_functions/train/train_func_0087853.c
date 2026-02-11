ast_cdr_setcid(struct ast_cdr *cdr, struct ast_channel *c)
{
	for (; cdr; cdr = cdr->next) {
		if (!ast_test_flag(cdr, AST_CDR_FLAG_LOCKED))
			set_one_cid(cdr, c);
	}
	return 0;
}
