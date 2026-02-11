newDuplicateBlock(TestCodeBlock *test_block) {
    CodeBlockHeader *new_block = allocCodeBlock(test_block->code_len);

    if(new_block != NULL) {

        new_block->u.ref_count = -1;


        memcpy(new_block + 1, test_block + 1, test_block->code_len);


        patchExternalJumps(test_block, new_block);


        FLUSH_CACHE(new_block + 1, test_block->code_len);
    }

    return new_block;
}
