genBlocks (generation *gen)
{
    ASSERT(countBlocks(gen->blocks) == gen->n_blocks);
    ASSERT(countBlocks(gen->large_objects) == gen->n_large_blocks);
    return gen->n_blocks + gen->n_old_blocks +
	    countAllocdBlocks(gen->large_objects);
}
