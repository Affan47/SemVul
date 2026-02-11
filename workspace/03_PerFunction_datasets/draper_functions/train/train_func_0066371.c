post_cdr(struct ast_cdr *cdr)
{
	struct ast_cdr_beitem *i;

	for ( ; cdr ; cdr = cdr->next) {
		if (!unanswered && cdr->disposition < AST_CDR_ANSWERED && (ast_strlen_zero(cdr->channel) || ast_strlen_zero(cdr->dstchannel))) {

			ast_set_flag(cdr, AST_CDR_FLAG_POST_DISABLED);
			continue;
		}


		if (ast_test_flag(cdr, AST_CDR_FLAG_DIALED) && !ast_test_flag(cdr, AST_CDR_FLAG_ORIGINATED)) {
			ast_set_flag(cdr, AST_CDR_FLAG_POST_DISABLED);
			continue;
		}

		check_post(cdr);
		ast_set_flag(cdr, AST_CDR_FLAG_POSTED);
		if (ast_test_flag(cdr, AST_CDR_FLAG_POST_DISABLED))
			continue;
		AST_RWLIST_RDLOCK(&be_list);
		AST_RWLIST_TRAVERSE(&be_list, i, list) {
			i->be(cdr);
		}
		AST_RWLIST_UNLOCK(&be_list);
	}
}
