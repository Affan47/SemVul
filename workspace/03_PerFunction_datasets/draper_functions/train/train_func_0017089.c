execute(match_ty *mp, string_ty *actual, const expr_position_ty *pp)
{
    match_cook_ty   *this;
    size_t          j;
    int             result;

    trace(("match_cook::execute(mp = %p, actual = %p)\n{\n", mp, actual));
    trace(("actual = \"%s\";\n", actual->str_text));
    this = (match_cook_ty *)mp;
#ifdef DEBUG
    check_magic(this, __LINE__, MAGIC_EXECUTED);
#endif


    for (j = 0; j < SIZEOF(this->fill); ++j)
    {
        if (this->fill[j])
        {
            str_free(this->fill[j]);
            this->fill[j] = 0;
        }
    }


    result =
        attempt_inner
        (
            this,
            this->formal->str_text,
            this->formal->str_text + this->formal->str_length,
            actual->str_text,
            actual->str_text + actual->str_length,
            pp
        );
#ifdef DEBUG
    if (result <= 0)
        this->magic = MAGIC_COMPILED;
#endif
    trace(("return %d;\n", result));
    trace(("}\n"));
    return result;
}
