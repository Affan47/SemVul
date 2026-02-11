ompfbe_get_index_of_qr_block(Block *head,
                                 qr_operator ope,
                                 Quadruple *target_qr,
                                 int pe_number,
                                 int *count)
{
    Block *block;
    int ret;
    int save;

    for (block = head; block != NULL; block = block->next) {
        ret = ompfbe_get_index_of_qr_pe_stm(
            block->pre_head, ope, target_qr, pe_number, count);

        save = *count;
        if(ret)
            return TRUE;

        if (block->inner != NULL) {
            ret = ompfbe_get_index_of_qr_block(
                block->inner, ope, target_qr, pe_number, count);
            if(ret)
                return TRUE;
            *count = save + ompfbe_count_qr_operator(block->inner, ope,
                                                     FALSE, TRUE, TRUE);
        }

        ret = ompfbe_get_index_of_qr_pe_stm(
            block->post_head, ope, target_qr, pe_number, count);

        if(ret)
            return TRUE;
    }

    return FALSE;
}
