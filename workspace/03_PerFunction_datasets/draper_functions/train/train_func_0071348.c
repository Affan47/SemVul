image_process_line(char *line, uint32 ispublic)
{
    char imagename[MAX_BUF], filename[MAX_BUF];
    uint32 checksum;

    if (line[0] == '#') return;

    if (sscanf(line, "%s %u %s", imagename, &checksum, filename)==3) {
        image_add_hash(imagename, filename, checksum, ispublic);
    } else {
        LOG(LOG_WARNING,"common::image_process_line","Did not parse line %s properly?", line);
    }
}
