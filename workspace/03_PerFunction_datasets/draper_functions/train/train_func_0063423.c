codeComp(char *code_pntr, int code_len, CodeBlockHeader *hashed_block) {
    if(code_len != hashed_block->code_len)
        return FALSE;

    return memcmp(code_pntr, hashed_block + 1, code_len) == 0;
}
