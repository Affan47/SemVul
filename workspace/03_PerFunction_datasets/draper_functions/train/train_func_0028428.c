find_subchannel_by_instance_reference(struct skinny_device *d, int instance, int reference)
{
	struct skinny_line *l = find_line_by_instance(d, instance);
	struct skinny_subchannel *sub;

	if (!l) {
		return NULL;
	}


	if (!reference)
		sub = AST_LIST_FIRST(&l->sub);
	else {
		AST_LIST_TRAVERSE(&l->sub, sub, list) {
			if (sub->callid == reference)
				break;
		}
	}
	if (!sub) {
		ast_log(LOG_WARNING, "Could not find subchannel with reference '%d' on '%s'\n", reference, d->name);
	}
	return sub;
}
