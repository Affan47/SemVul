option_set_order(option_t *opt, double order)
{
    option_t *prev;


    if (opt == optionlist_sorted_by_order)
        optionlist_sorted_by_order = opt->next_by_order;
    else {
        for (prev = optionlist_sorted_by_order;
             prev && prev->next_by_order != opt;
             prev = prev->next_by_order);
        prev->next_by_order = opt->next_by_order;
    }

    opt->order = order;


    if (!optionlist_sorted_by_order)
        optionlist_sorted_by_order = opt;
    else if (optionlist_sorted_by_order->order > opt->order) {
        opt->next_by_order = optionlist_sorted_by_order;
        optionlist_sorted_by_order = opt;
    }
    else {
        for (prev = optionlist_sorted_by_order;
            prev->next_by_order && prev->next_by_order->order < opt->order;
            prev = prev->next_by_order);
        opt->next_by_order = prev->next_by_order;
        prev->next_by_order = opt;
    }
}
