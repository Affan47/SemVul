constructor(match_ty *mp)
{
    match_cook_ty   *this;
    size_t          j;

    trace(("match_cook::constructor(mp = %08X)\n{\n", mp));
    this = (match_cook_ty *) mp;
    this->formal = 0;
    for (j = 0; j < SIZEOF(this->fill); ++j)
        this->fill[j] = 0;
#ifdef DEBUG
    this->magic = MAGIC_CONSTRUCTED;
#endif
    trace(("}\n"));
}
