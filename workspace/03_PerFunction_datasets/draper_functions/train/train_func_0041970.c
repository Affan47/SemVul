bfg_link_nodes(Module_table *module, Block *outer, List *order)
{
    List *li;

    unlink_linked_nodes(order);

    for (li = order; li != NULL; li = li->next) {
        BfgNode *node = (BfgNode *)li->data;
        Block *block = make_predicated_block(module, node);

        block_insert_inner_tail0(outer, block, TRUE);
    }
}
