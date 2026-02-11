cdiff_cmd_del(const char *cmdstr, struct cdiff_ctx *ctx, char *lbuf, unsigned int lbuflen)
{
	char *arg;
	struct cdiff_node *pt, *last, *new;
	unsigned int lineno;


    if(!(arg = cdiff_token(cmdstr, 1, 0))) {
	logg("!cdiff_cmd_del: Can't get first argument\n");
	return -1;
    }
    lineno = (unsigned int) atoi(arg);
    free(arg);

    if(!(arg = cdiff_token(cmdstr, 2, 1))) {
	logg("!cdiff_cmd_del: Can't get second argument\n");
	return -1;
    }

    new = (struct cdiff_node *) calloc(1, sizeof(struct cdiff_node));
    if(!new) {
	logg("!cdiff_cmd_del: Can't allocate memory for cdiff_node\n");
	free(arg);
	return -1;
    }
    new->str = arg;
    new->lineno = lineno;

    if(!ctx->del_start) {

	ctx->del_start = new;

    } else {

	if(lineno < ctx->del_start->lineno) {
	    new->next = ctx->del_start;
	    ctx->del_start = new;

	} else {
	    pt = ctx->del_start;

	    while(pt) {
		last = pt;
		if((pt->lineno < lineno) && (!pt->next || lineno < pt->next->lineno))
		    break;

		pt = pt->next;
	    }

	    new->next = last->next;
	    last->next = new;
	}
    }

    return 0;
}
