set_hmdf_info_for_any_layer(Module_table *head)
{
    Module_table *mpt;

    for (mpt = head; mpt != NULL; mpt = mpt->next) {
        if (mpt->kind != MODULE_BLOCKDATA) {
            set_hmdf_info_for_any_layer_for_blocks(mpt->block_head);
            cut_all_hmdf_children(mpt->block_head);
            remaking_hmdf_tree(mpt->block_head, mpt->super_hmdf);
        }
    }
}
