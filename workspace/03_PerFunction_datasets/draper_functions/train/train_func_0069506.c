sixtp_destroy_node(sixtp *sp, GHashTable *corpses)
{
    g_return_if_fail(sp);
    g_return_if_fail(corpses);
    g_hash_table_foreach(sp->child_parsers, sixtp_destroy_child, corpses);
    g_hash_table_destroy(sp->child_parsers);
    g_free(sp);
}
