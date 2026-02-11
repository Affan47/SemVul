speck_decode_I(int **channel, int channel_size, pixel_set *I,
                         linked_list **LIS_slots, linked_list *LSP,
                         bit_buffer *bb, int threshold)
{
    pixel_set new_sets[3];
    int result;
    int i;


    split_set(I, I, &new_sets[0], &new_sets[1], &new_sets[2], channel_size);


    for (i = 0; i < 3; i++) {
        list_node *node = alloc_list_node(sizeof(pixel_set));
        assign_set(node, &new_sets[i]);

        result = speck_unprocess_S(channel, channel_size, node,
                                   NULL, LIS_slots, LSP, bb,
                                   threshold, STAGE_I);

        if (result == BIT_BUFFER_UNDERFLOW) {
            free_list_node(node);
            return result;
        }
    }


    result = speck_unprocess_I(channel, channel_size, I,
                               LIS_slots, LSP, bb, threshold);

    return result;
}
