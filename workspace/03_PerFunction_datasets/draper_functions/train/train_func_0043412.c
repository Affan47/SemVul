RadixMap_delete(RadixMap *map, RMElement *el)
{
    check(map->end > 0, "There is nothing to delete.");
    check(el != NULL, "Can't delete a NULL element.");

    el->data.key = UINT32_MAX;

    if(map->end > 1) {

        RadixMap_sort(map);
    }

    map->end--;

    return 0;
error:
    return -1;
}
