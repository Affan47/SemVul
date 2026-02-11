optimize(int result, bool keepLvalue)
{
    if (e0)
        e0 = e0->optimize(WANTvalue);
    for (size_t i = 0; i < exps->dim; i++)
    {
        Expression *e = (*exps)[i];
        e = e->optimize(WANTvalue);
        (*exps)[i] = e;
    }
    return this;
}
