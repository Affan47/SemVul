set_loop_values(void *user, const struct value *values,
    int n_values)
{
	struct loop *loop = user;

	switch (n_values) {
	case 2:
		if (loop->to.expr)
			free_expr(loop->to.expr);
		loop->to.expr = values->next->expr;

	case 1:
		if (loop->from.expr)
			free_expr(loop->from.expr);
		loop->from.expr = values->expr;
		break;
	case 0:
		break;
	default:
		abort();
	}
}
