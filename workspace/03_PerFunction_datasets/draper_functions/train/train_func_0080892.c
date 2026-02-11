APar_MergeTempFile(FILE* dest_file, FILE *src_file, uint32_t src_file_size, uint32_t dest_position, char* &buffer) {
    uint32_t file_pos = 0;
    while (file_pos <= src_file_size) {
        if (file_pos + max_buffer <= src_file_size) {
            fseeko(src_file, file_pos, SEEK_SET);
            fread(buffer, 1, (size_t) max_buffer, src_file);


#if defined(_MSC_VER)
            fpos_t file_offset = dest_position + file_pos;
#elif defined(__GLIBC__)
            fpos_t file_offset =
                { 0 };
            file_offset.__pos = dest_position + file_pos;
#else
            off_t file_offset = dest_position + file_pos;
#endif
            fsetpos(dest_file, &file_offset);
            fwrite(buffer, (size_t) max_buffer, 1, dest_file);
            file_pos += max_buffer;

        }
        else {
            fseeko(src_file, file_pos, SEEK_SET);
            fread(buffer, 1, (size_t) (src_file_size - file_pos), src_file);
#if defined(_MSC_VER)
            fpos_t file_offset = dest_position + file_pos;
#elif defined(__GLIBC__)
            fpos_t file_offset =
                { 0 };
            file_offset.__pos = dest_position + file_pos;
#else
            off_t file_offset = dest_position + file_pos;
#endif
            fsetpos(dest_file, &file_offset);
            fwrite(buffer, (size_t) (src_file_size - file_pos), 1, dest_file);
            file_pos += src_file_size - file_pos;
            break;
        }
    }
    return;
}
