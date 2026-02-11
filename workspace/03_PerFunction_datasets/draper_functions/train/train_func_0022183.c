wmem_test_map(void)
{
    wmem_allocator_t *allocator;
    wmem_map_t       *map;
    gchar            *str_key;
    unsigned int      i;
    void             *ret;

    allocator = wmem_allocator_new(WMEM_ALLOCATOR_STRICT);


    map = wmem_map_new(allocator, g_direct_hash, g_direct_equal);
    g_assert(map);

    for (i=0; i<CONTAINER_ITERS; i++) {
        ret = wmem_map_insert(map, GINT_TO_POINTER(i), GINT_TO_POINTER(777777));
        g_assert(ret == NULL);
        ret = wmem_map_insert(map, GINT_TO_POINTER(i), GINT_TO_POINTER(i));
        g_assert(ret == GINT_TO_POINTER(777777));
        ret = wmem_map_insert(map, GINT_TO_POINTER(i), GINT_TO_POINTER(i));
        g_assert(ret == GINT_TO_POINTER(i));
    }
    for (i=0; i<CONTAINER_ITERS; i++) {
        ret = wmem_map_lookup(map, GINT_TO_POINTER(i));
        g_assert(ret == GINT_TO_POINTER(i));
        ret = wmem_map_remove(map, GINT_TO_POINTER(i));
        g_assert(ret == GINT_TO_POINTER(i));
        ret = wmem_map_lookup(map, GINT_TO_POINTER(i));
        g_assert(ret == NULL);
        ret = wmem_map_remove(map, GINT_TO_POINTER(i));
        g_assert(ret == NULL);
    }
    wmem_free_all(allocator);

    map = wmem_map_new(allocator, wmem_str_hash, g_str_equal);
    g_assert(map);


    for (i=0; i<CONTAINER_ITERS; i++) {
        str_key = wmem_test_rand_string(allocator, 1, 64);
        wmem_map_insert(map, str_key, GINT_TO_POINTER(i));
        ret = wmem_map_lookup(map, str_key);
        g_assert(ret == GINT_TO_POINTER(i));
    }

    wmem_destroy_allocator(allocator);
}
