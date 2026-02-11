ReadUptoMatch(FILE * infile, const char *scanchars)
{
    int bufindex = 0;
    int c;

    if (feof(infile) != 0)
        return NULL;

    if (buffer == NULL) {
        buffer = (char *) malloc(BUFFER_INCREMENT * sizeof(char));
        if (buffer == NULL) {
            diagnostics(ERROR, "Cannot allocate memory for input buffer");
            exit(1);
        }
        bufsize = BUFFER_INCREMENT;
    }

    while ((c = getc(infile)) != EOF) {

        if (c == CR || c == LF)
            c = '\n';

        if (strchr(scanchars, c))
            break;

        if (c == (int) '\0')
            continue;

        buffer[bufindex++] = (char) c;
        if (bufindex >= bufsize) {
            bufsize += BUFFER_INCREMENT;
            buffer = (char *) realloc(buffer, bufsize);
            if (buffer == NULL) {
                diagnostics(ERROR, "Cannot allocate memory for input buffer");
                exit(1);
            }
        }
    }
    buffer[bufindex] = '\0';
    if (c != EOF)
        ungetc(c, infile);

    return buffer;
}
