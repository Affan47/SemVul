init_block_pa_info(Block *block)
{
    Block *b;

    free_pa_info(block->in_pa_info);
    free_pa_info(block->unified_pa_info);
    free_pa_info(block->out_pa_info);
    block->in_pa_info = NULL;
    block->unified_pa_info = NULL;
    block->out_pa_info = NULL;
    if (block->inner != NULL) {
        for (b = block->inner; b != NULL; b = b->next) {
            init_block_pa_info(b);
        }
    }
}
