expr_stat_in_func(struct stmt *fs)
{
	struct stmt *cs;
	struct expr *ce;
	struct constraint *c;

	for (cs = fs->stmt_first; cs; cs = cs->next) {
		switch (cs->type) {
		case STMT_NONE:
			assert(0);

		case STMT_CASE:
		case STMT_DEFAULT:
		case STMT_WHILE:
		case STMT_DO_WHILE:
		case STMT_FOR:
		case STMT_CONTINUE:
		case STMT_BREAK:
		case STMT_BLOCK:

			assert(0);

		case STMT_NULL:
		case STMT_LABEL:
		case STMT_GOTO:
			break;

		case STMT_EXPR:
			switch (cs->expr0->type) {
			case EXPR_ASSIGN:
				if (cs->expr0->expr0->type == EXPR_IDENTIFIER) {
					cs->expr0->expr0->declaration->assign_expr
							= cs->expr0->expr1;
					cs->expr0->expr0->declaration->wcount++;
				} else if (cs->expr0->expr0->type == EXPR_STAR) {
					expr_stat_in_expr(cs->expr0->expr0);
				}
				expr_stat_in_expr(cs->expr0->expr1);
				break;

			case EXPR_FUNC:
				expr_stat_in_expr(cs->expr0->expr0);
				for (ce = cs->expr0->expr1->first;
				    ce;
				    ce = ce->next) {
					expr_stat_in_expr(ce);
				}
				break;

			default:

				expr_stat_in_expr(cs->expr0);
				break;
			}
			break;

		case STMT_IF:
		case STMT_SWITCH:
			expr_stat_in_expr(cs->expr0);
			break;

		case STMT_RETURN:
			if (cs->expr0) {
				expr_stat_in_expr(cs->expr0);
			}
			break;

		case STMT_VA_START:
		case STMT_VA_END:

			break;

		case STMT_ASM:
			if (cs->output) {
				for (c = cs->output->first; c; c = c->next) {
					if (c->expr->type == EXPR_IDENTIFIER) {
						c->expr->declaration->wcount++;
						c->expr->declaration->rcount++;
					}
				}
			}
			if (cs->input) {
				for (c = cs->input->first; c; c = c->next) {
					expr_stat_in_expr(c->expr);
				}
			}
			break;

		default:
			assert(0);
		}
	}
}
