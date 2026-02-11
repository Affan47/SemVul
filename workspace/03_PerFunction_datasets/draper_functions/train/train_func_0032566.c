static_scalar_manage_block(Block *block, const int level)
{
    Lm **lm;

    if (block->hmdf != NULL
        && block->hmdf->scheduling == SCHE_STATIC
        && block->hmdf->pe_num == 1
        && block->stasche_layer_info != NULL) {
        int lm_word;
        int dsm_word;
        int all_pe_num = block->hmdf->pe_num * block->hmdf->pc_num;
        List *head;

        if (all_pe_num == 1) return ;
        set_lm_dsm_word(level, &lm_word, &dsm_word);
        head = set_cmp_localize_blocks(block->inner, level);

        lm = init_local_memory_template(lm_word,
                                        dsm_word,
                                        ya_get_full_slot_size(level),
                                        ya_get_max_template_class(level),
                                        all_pe_num);
        stasche_lm_dt_block(block, lm, level);
        reset_cmp_localize_blocks(head);
        list_free(head);
    } else if (block->kind == SB) {
        Module_table *callee = sb_callee(block);
        IntSet target = (callee->kind == MODULE_FUNC) ? localized_func_set
            : localized_sub_set;
        if (!in_IntSet(target, callee->entry)) {
            static_scalar_manage_block_next(callee->block_head, level);
            add1_IntSet(target, callee->entry);
        }
    } else if (block->inner != NULL) {
        static_scalar_manage_block_next(block->inner, level);
    }
}
