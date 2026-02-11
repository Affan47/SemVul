array_range_semnode_list(Array_region_list_semnode *region_head)
{
    Array_region_list_semnode *region;
    List *li = NULL;

    for(region = region_head;
        region != NULL;
        region = region->next)
    {
        li = list_append(li, region->dim_head);
    }

    return li;
}
