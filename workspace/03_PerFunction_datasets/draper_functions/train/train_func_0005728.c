find_subchannel_by_reference(struct skinny_device *d, int reference)
{
	struct skinny_line *l;
	struct skinny_subchannel *sub = NULL;

	AST_LIST_TRAVERSE(&d->lines, l, list){
		AST_LIST_TRAVERSE(&l->sub, sub, list){
			if (sub->callid == reference)
				break;
		}
		if (sub)
			break;
	}

	if (!l) {
		ast_log(LOG_WARNING, "Could not find any lines that contained a subchannel with reference '%d' on device '%s'\n", reference, d->name);
	} else {
		if (!sub) {
			ast_log(LOG_WARNING, "Could not find subchannel with reference '%d' on '%s@%s'\n", reference, l->name, d->name);
		}
	}
	return sub;
}
