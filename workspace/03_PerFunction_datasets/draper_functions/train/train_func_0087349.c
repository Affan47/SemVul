repl_guessType(StoreEntry * entry, RemovalPolicyNode * node)
{
    if (node == &entry->repl)
	return TYPE_STORE_ENTRY;
    if (entry->mem_obj && node == &entry->mem_obj->repl)
	return TYPE_STORE_MEM;
    fatal("Heap Replacement: Unknown StoreEntry node type");
    return TYPE_UNKNOWN;
}
