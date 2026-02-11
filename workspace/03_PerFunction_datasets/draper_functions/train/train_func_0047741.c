check_loop_relation( Module_table *module,
                    SemTree *start, SemTree *end, SemTree *step)
{
    SemTree *c0 = make_semtree_const_int(0);
    int comp_step;
    int comp_range;
    Boolean ret;

    comp_step = compare_semtree(step, c0);
    if (comp_step == SYM_ERR) {
        ret = FALSE;
    } else {
        comp_range = compare_semtree(start, end);
        if (comp_range == SYM_ERR) {
            ret = FALSE;
        } else if ((comp_step > 0 && comp_range > 0)
                   || (comp_step < 0 && comp_range < 0)) {
            ret = TRUE;
        }else {
            ret = FALSE;
        }
    }

    return ret;
}
