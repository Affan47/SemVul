parse_number(struct parse_ctx *ctx)
{
    int number = 0, neg = 1;

    if (ctx->p >= ctx->pend)
	return NULL;

    if (*ctx->p == '-') {
	if (ctx->p + 1 >= ctx->pend)
	    return NULL;
	neg = -1;
	ctx->p += 1;
    }

    while (ctx->p < ctx->pend) {
	if (is_number(*ctx->p)) {
	    number = (number * 10) + (*ctx->p - '0');
	} else {
	    break;
	}
	ctx->p += 1;
    }

    return heim_number_create(number * neg);
}
