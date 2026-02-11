find_empty_block(int dev) {
    int prefix;
    const int blocks_free_size = MAX_BLOCK_SIZE/8;
    byte not_byte;
    int found = 0;
    int suffix = 0;
    int shift_mask;

    for (prefix = 0; prefix < blocks_free_size; prefix++) {
        if (device_array[dev].bitmap[prefix] != 0xff) {
            found = 1;
            not_byte = ~device_array[dev].bitmap[prefix];
            break;
        }
    }


    if (!found) {
        return ERROR_NO_FREE_BLOCKS;
    }


    shift_mask = 0x80;
    for (suffix = 0; suffix < 8; suffix++){
        if (not_byte & shift_mask) {
            break;
        }
        shift_mask >>= 1;
    }


    return (prefix << 3) + suffix;
}
