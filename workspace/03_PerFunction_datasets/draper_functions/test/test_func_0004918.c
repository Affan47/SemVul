range_alloc(coord_range_list_t *pcrl)
{
    coord_range_t *pcr;

    if (pcrl->freed) {
        pcr = pcrl->freed;
        pcrl->freed = pcr->next;
    } else if (pcrl->local.next < pcrl->local.limit)
        pcr = pcrl->local.next++;
    else {
        pcr = gs_alloc_struct(pcrl->memory, coord_range_t, &st_coord_range,
                              "range_alloc");
        if (pcr == 0)
            return 0;
        pcr->alloc_next = pcrl->allocated;
        pcrl->allocated = pcr;
    }
    return pcr;
}
