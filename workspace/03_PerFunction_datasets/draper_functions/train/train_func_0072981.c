dump_acl_list(StoreEntry * entry, acl_list * head)
{
    acl_list *l;
    for (l = head; l; l = l->next) {
	storeAppendPrintf(entry, " %s%s",
	    l->op ? null_string : "!",
	    l->acl->name);
    }
}
