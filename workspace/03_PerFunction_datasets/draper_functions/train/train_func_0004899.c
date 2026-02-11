output_hash(ostream& out, const char* data, long data_len) const {
    int i;
    long cur_offset = 0;

    if (opts->with_size) {
        output_hex(out, data, 8);
        out << "|";
        cur_offset += 8;
    }

    if (opts->header_block_count) {
        for (i = 0; i < opts->header_block_count - 1; i++) {
            output_hex(out, data + cur_offset + i*opts->block_size, opts->block_size);
            out << ",";
        }
        output_hex(out, data + cur_offset + i*opts->block_size, opts->block_size);
        out << "|";
        cur_offset += opts->header_block_count * opts->block_size;
    }

    for (i = 0; i < opts->block_count-1; i++) {
        output_hex(out, data + cur_offset + i*opts->block_size, opts->block_size);
        out << ",";
    }
    output_hex(out, data + cur_offset + i*opts->block_size, opts->block_size);
}
