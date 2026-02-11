ast_cdr_disposition(struct ast_cdr *cdr, int cause)
{
	int res = 0;

	for (; cdr; cdr = cdr->next) {
		switch (cause) {

		case AST_CAUSE_BUSY:
			ast_cdr_busy(cdr);
			break;
		case AST_CAUSE_NO_ANSWER:
			ast_cdr_noanswer(cdr);
			break;
		case AST_CAUSE_NORMAL_CIRCUIT_CONGESTION:
			ast_cdr_congestion(cdr);
			break;
		case AST_CAUSE_NORMAL:
			break;
		default:
			res = -1;
		}
	}
	return res;
}
