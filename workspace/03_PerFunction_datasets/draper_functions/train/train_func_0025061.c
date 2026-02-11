slot_has_other_module_entry(Slot *slot, Block *block)
{
    List *li;

    if (flg_lad_multi_module_div) {
        for (li = slot->group_info->lm_blk_list; li != NULL; li = li->next) {
            Block *b = li->data;
            if (b->module != block->module) {
                return TRUE;
            }
        }
    }
    return FALSE;
}
