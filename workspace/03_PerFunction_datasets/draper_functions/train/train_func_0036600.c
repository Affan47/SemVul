cmp_sub_data_elem(Sub_data *s0, Sub_data *s1)
{
    if (s0->kind == KIND_CONST && s1->kind == KIND_CONST)
        return 0;

    if (s0->kind == KIND_CONST)
        return 1;

    if (s1->kind == KIND_CONST)
        return -1;

    if (s0->kind == s1->kind)
        return s0->entry - s1->entry;

    if (s0->kind == KIND_VAR && s1->kind == KIND_ARRAY)
        return 1;

    if (s0->kind == KIND_ARRAY && s1->kind == KIND_VAR)
        return -1;

    fatal("koko ni ha konai\n");
    return 0;
}
