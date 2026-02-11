n_or_more(struct obj *obj)
{
    if (obj == uchain)
    {
        return false;
    }
    return (obj->quan >= val_for_n_or_more);
}
