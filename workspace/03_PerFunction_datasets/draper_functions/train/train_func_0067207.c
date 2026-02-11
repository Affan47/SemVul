wmem_test_allocator(wmem_allocator_type_t type, wmem_verify_func verify,
        int iterations)
{
    int i;
    char *ptrs[MAX_SIMULTANEOUS_ALLOCS];
    wmem_allocator_t *allocator;

    allocator = wmem_allocator_force_new(type);

    if (verify) (*verify)(allocator);


    wmem_test_allocator_det(allocator, verify, 8);

    wmem_test_allocator_det(allocator, verify, 64);

    wmem_test_allocator_det(allocator, verify, 512);

    for (i=0; i<MAX_SIMULTANEOUS_ALLOCS; i++) {
        ptrs[i] = wmem_alloc0_array(allocator, char, 32);
    }

    if (verify) (*verify)(allocator);
    wmem_free_all(allocator);
    wmem_gc(allocator);
    if (verify) (*verify)(allocator);


    for (i=0; i<MAX_SIMULTANEOUS_ALLOCS; i++) {
        ptrs[i] = NULL;
    }


    for (i=0; i<iterations; i++) {
        gint ptrs_index;
        gint new_size;


        ptrs_index = g_test_rand_int_range(0, MAX_SIMULTANEOUS_ALLOCS);

        if (ptrs[ptrs_index] == NULL) {


            new_size = g_test_rand_int_range(0, MAX_ALLOC_SIZE);

            ptrs[ptrs_index] = (char *) wmem_alloc0(allocator, new_size);
        }
        else if (g_test_rand_bit()) {


            new_size = g_test_rand_int_range(0, MAX_ALLOC_SIZE);

            ptrs[ptrs_index] = (char *) wmem_realloc(allocator,
                    ptrs[ptrs_index], new_size);

            memset(ptrs[ptrs_index], 0, new_size);
        }
        else {


            wmem_free(allocator, ptrs[ptrs_index]);
            ptrs[ptrs_index] = NULL;
        }
        if (verify) (*verify)(allocator);
    }

    wmem_destroy_allocator(allocator);
}
