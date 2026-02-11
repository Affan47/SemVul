read_redirected(void)
{
    int         size = MEM_INC;
    char        *p;
    char        *line;
    char        *end;

    p = line = malloc(sizeof(char) * size);
    if (!p)
	return NULL;

    end = p + size;
    while (1) {
        if (p == end) {
            int oldpos = end - line;

            size += MEM_INC;
            p = line = realloc(line, sizeof(char) * size);
	    if (!p)
		return NULL;
            end = p + size;

            p += oldpos;
        }
        if (read(0, p, 1) <= 0) {

            free(line);
            return NULL;
        }
        if (*p == '\n')
            break;
        p++;
    }
    *p = '\0';

    return line;
}
