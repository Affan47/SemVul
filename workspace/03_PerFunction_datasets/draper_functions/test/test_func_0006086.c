quicksort_iterative(uint32_t n, uint32_t *in, uint32_t *out)
{
    (void) in;

    const uint32_t max_stack_size = ((int) log(n)/log(2)) + 1;
    uint32_t stack_count;
    uint32_t *stack_n = malloc(4 * max_stack_size);
    uint32_t **stack_out = malloc(sizeof(uint32_t*) * max_stack_size);

    stack_count = 1;
    stack_n[0] = n;
    stack_out[0] = out;

    while(stack_count > 0) {
        uint32_t cur_n = stack_n[stack_count - 1];
        uint32_t *cur_out = stack_out[stack_count - 1];
        stack_count--;

        if(cur_n <= 1)
            continue;

        uint32_t store_idx = quicksort_partition_helper(cur_n, cur_out);


        if(store_idx <= cur_n / 2) {
            stack_n[stack_count] = cur_n - store_idx - 1;
            stack_out[stack_count] = &cur_out[store_idx + 1];
            stack_count++;
            stack_n[stack_count] = store_idx;
            stack_out[stack_count] = cur_out;
            stack_count++;
        } else {
            stack_n[stack_count] = store_idx;
            stack_out[stack_count] = cur_out;
            stack_count++;
            stack_n[stack_count] = cur_n - store_idx - 1;
            stack_out[stack_count] = &cur_out[store_idx + 1];
            stack_count++;
        }
    }

    free(stack_n);
    free(stack_out);
}
