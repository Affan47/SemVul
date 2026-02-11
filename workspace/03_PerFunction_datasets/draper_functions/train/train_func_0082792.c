shrink_argument_table_for_cmp(Block *outer)
{
    IntSet mark;
    List *target_sb_list = NULL;

    construct_IntSet(mark, outer->mt_num + 1);

    for (target_sb_list = make_shrink_target_sb_list(outer, mark);
         target_sb_list != NULL;
         target_sb_list = make_shrink_target_sb_list(outer, mark)) {

        shrink_argument_table0(target_sb_list);
    }

    destruct_IntSet(mark);
}
