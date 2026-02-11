http_process_header_line(struct httplocalfile *lf, char *line)
{
    char *s;

    s = http_split_header(line);

    if(strcasecmp("content-length:", line) == 0) {
        char *end;
        avoff_t size;
        size = strtol(s, &end, 10);
        while(*end && isspace((unsigned char) *end))
            end++;

        if(!*end)
            lf->ent->size = size;
    }
}
