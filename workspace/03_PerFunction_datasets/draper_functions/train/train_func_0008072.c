rev_ref_is_ready (char *name, rev_list *source, rev_ref *ready)
{
    for (; source; source = source->next) {
	rev_ref *head = rev_find_head(source, name);
	if (head) {
	    if (head->parent && !rev_ref_find_name(ready, head->parent->name))
		    return 0;
	}
    }
    return 1;
}
