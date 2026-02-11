gmtsub(const struct timeval *timep, const long offset, struct ast_tm *tmp)
{
	struct ast_tm *	result;
	struct state *sp;

	AST_LIST_LOCK(&zonelist);
	AST_LIST_TRAVERSE(&zonelist, sp, list) {
		if (!strcmp(sp->name, "UTC"))
			break;
	}

	if (!sp) {
		if (!(sp = (struct state *) ast_calloc(1, sizeof *sp)))
			return NULL;
		gmtload(sp);
		AST_LIST_INSERT_TAIL(&zonelist, sp, list);
	}
	AST_LIST_UNLOCK(&zonelist);

	result = timesub(timep, offset, sp, tmp);
#ifdef TM_ZONE


	if (offset != 0)
		tmp->TM_ZONE = "    ";
	else
		tmp->TM_ZONE = sp->chars;
#endif
	return result;
}
