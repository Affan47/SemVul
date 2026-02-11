renumber_filter(struct filter *filter)
{
    while(filter) {
        if(filter->ifname)
            filter->ifindex = if_nametoindex(filter->ifname);
        filter = filter->next;
    }
}
