begin_block_sequence(char* buffer) {
    this->buffer = buffer;
    ranges.str("");
    total_block_size = 0;
}
