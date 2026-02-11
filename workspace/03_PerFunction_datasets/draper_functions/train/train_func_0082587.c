zend(i_ctx_t *i_ctx_p)
{
    if (ref_stack_count_inline(&d_stack) == min_dstack_size) {

        return_error(e_dictstackunderflow);
    }
    while (dsp == dsbot) {

        ref_stack_pop_block(&d_stack);
    }
    dsp--;
    dict_set_top();
    return 0;
}
