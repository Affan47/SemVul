include_lm_assigned_block(Block *block_head)
{
    Block *bpt;
    Boolean ret = FALSE;
    for (bpt = block_head; bpt != NULL; bpt = bpt->next) {
        if (bpt->cmp_localize != NULL) {
            return TRUE;
        } else if (bpt->inner != NULL) {
            if(include_lm_assigned_block(bpt->inner))
                return TRUE;
        }
    }
    return ret;
}
