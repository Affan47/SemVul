tst_collect_build(void *value, tst_collect_t *results)
{
    if(!results->tester || results->tester(value, results->key, results->len)) {
        lnode_t *node = lnode_create(value);
        list_append(results->values, node);
    }
}
