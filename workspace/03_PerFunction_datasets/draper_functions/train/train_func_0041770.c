div_num_analy_loops(Hmdf_tlg_info *hti, Block *block, int bound, Lad_opt *lad_opt)
{
    List *block_list;
    List *li;
    int iter, div_num;

    block_list = make_target_block_list(block->inner, bound, lad_opt);

    for (li = block_list; li != NULL; li = li->next) {
        Block *b = li->data;

        iter = get_loop_iter(b);
        div_num = set_div_num(hti, b->total_array_size, bound, iter);
        make_simple_lad_directive(b, div_num);
    }

    list_free(block_list);
}
