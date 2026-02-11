add_scatter_item(Scatter *first, Scatter *last)
{
    Scatter    *tmp = first;

    while (tmp->next)
	tmp = tmp->next;
    tmp->next = last;

    return first;
}
