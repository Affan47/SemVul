op_show_find(i_ctx_t *i_ctx_p)
{
    uint index = op_show_find_index(i_ctx_p);

    if (index == 0)
        return 0;
    return r_ptr(ref_stack_index(&e_stack, index - (snumpush - 1)),
                 gs_text_enum_t);
}
