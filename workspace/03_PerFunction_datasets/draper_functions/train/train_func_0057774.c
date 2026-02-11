netsnmp_subtree_find_first(const char *context_name)
{
    subtree_context_cache *ptr;

    if (!context_name) {
        context_name = "";
    }

    DEBUGMSGTL(("subtree", "looking for subtree for context: \"%s\"\n",
		context_name));
    for (ptr = context_subtrees; ptr != NULL; ptr = ptr->next) {
        if (ptr->context_name != NULL &&
	    strcmp(ptr->context_name, context_name) == 0) {
            DEBUGMSGTL(("subtree", "found one for: \"%s\"\n", context_name));
            return ptr->first_subtree;
        }
    }
    DEBUGMSGTL(("subtree", "didn't find a subtree for context: \"%s\"\n",
		context_name));
    return NULL;
}
