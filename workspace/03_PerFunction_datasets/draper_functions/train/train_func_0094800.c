modify_sb_super_hmdf_info(Block *head, Hmdf_table *parent)
{
    Block *bpt;

    for (bpt = head; bpt != NULL; bpt = bpt->next) {
        if (bpt->kind == SB) {
            Module_table *sb = sb_callee(bpt);
            sb->super_hmdf->pc_num = parent->pc_num;
            sb->super_hmdf->pe_num = parent->pe_num;
            sb->super_hmdf->depth++;
        }
    }
}
