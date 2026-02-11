reorder_blocks(Module_table *module_head)
{
    Module_table *mpt;

    cfa(module_head);
    for (mpt = module_head; mpt != NULL; mpt = mpt->next) {
#ifdef DEBUG_REORDER_BLOCKS
	mfprintf(stderr, "reordering blocks in %B\n", mpt->block_head);
#endif
	reorder_inner_blocks(mpt->block_head);
    }
}
