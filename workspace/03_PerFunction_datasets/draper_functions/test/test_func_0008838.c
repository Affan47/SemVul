RadixMap_add(RadixMap *map, uint32_t key, uint32_t value)
{
    check(key < UINT32_MAX, "Key can't be equal to UINT32_MAX.");

    RMElement element = {.data = {.key = key, .value = value}};
    check(map->end + 1 < map->max, "RadixMap is full.");

    map->contents[map->end++] = element;

    RadixMap_sort(map);

    return 0;

error:
    return -1;
}
