output_bits(struct uo_compression *co,
                       unsigned char *dest,
                       size_t dest_max_len,
                       size_t *dest_indexp) {
    while (co->bit >= 8) {
        if (*dest_indexp >= dest_max_len)
            return -1;
        co->bit -= 8;
        dest[(*dest_indexp)++] = (co->out_data >> co->bit) & 0xff;
    }

    return 0;
}
