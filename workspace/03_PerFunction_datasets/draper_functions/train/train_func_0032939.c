asi_get_sub_list_of_dim(Array_subscript_info *asi, int dim)
{
    int d;
    Sub_list *sub;

    d = 0;
    for (sub = asi->sub_info; sub != NULL; sub = sub->next_dim) {
        if (d == dim)
            break;
        d++;
    }

    return sub;
}
