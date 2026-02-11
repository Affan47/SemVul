writeRaw(std::vector<char>& buffer, int start, int pixel_count) {

    raw_count += pixel_count;

    int written = 0;

    while(pixel_count > 0) {
        int write_count = std::min(128, pixel_count);

        char counter_byte = write_count-1;

        out->write((char*)&counter_byte, 1);

        for(int i=0; i < write_count; i++) {
            out->write(&(buffer[start+(i+written)*components]), components);
        }

        pixel_count -= write_count;
        written += write_count;
    }
}
