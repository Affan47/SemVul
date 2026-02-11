malloc_hmdf_info_of_control_layer( Hmdf_information *hmdf_info, Block *bpt )
{
    Hmdf_information *ret;

    ret = malloc_Hmdf_information_p();
    ret->block = bpt;
    ret->kind = TYPE_NON;
    ret->pe_num = 1;
    ret->pc_num = 1;
    ret->pcpe_num = -1;
    ret->parent_pc_num = 1;
    ret->seq_cost = hmdf_info->seq_cost;
    ret->div_number = 1;
    ret->iteration_times = 1;
    ret->level = hmdf_info->seq_cost;
    ret->div_loop_level = hmdf_info->div_loop_level;
    ret->hierarchical_level = hmdf_info->hierarchical_level;
    ret->inner_inline_level = (hmdf_info->block->kind == SB) ?
        hmdf_info->inner_inline_level : hmdf_info->seq_cost;
    ret->inner_inline_div_loop_level = (hmdf_info->block->kind == SB) ?
        hmdf_info->inner_inline_div_loop_level : hmdf_info->seq_cost;
    ret->para = 1;
    ret->div_loop_para = hmdf_info->div_loop_para;
    ret->hierarchical_para = hmdf_info->hierarchical_para;
    ret->inner_inline_para = (hmdf_info->block->kind == SB) ?
        hmdf_info->inner_inline_para : 1;
    ret->inner_inline_div_loop_para = (hmdf_info->block->kind == SB) ?
        hmdf_info->inner_inline_div_loop_para : 1;
    ret->max_para = hmdf_info->max_para;
    ret->inner_inl_max_para = hmdf_info->inner_inl_max_para;
    ret->level_tree = malloc_Branch_block();
    ret->level_tree->current_block = hmdf_info->block;
    ret->div_loop_level_tree = malloc_Branch_block();
    ret->div_loop_level_tree->current_block = hmdf_info->block;
    ret->h_level_tree = malloc_Branch_block();
    ret->h_level_tree->current_block = hmdf_info->block;
    ret->next = NULL;
    ret->prev = NULL;
    ret->is_pe_control_layer = TRUE;

    return ret;
}
