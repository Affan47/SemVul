getSpacedTexUntil(char *target, int raw)


{
    enum { BUFFSIZE = 16000 };
    char buffer[BUFFSIZE];
    char *s;
    int buffer_pos, target_pos, target_len, max_buffer_pos, start_pos;

    PushTrackLineNumber(FALSE);

    diagnostics(5, "getSpacedTexUntil target = <%s> raw_search = %d ", target, raw);

    buffer_pos = 0;
    target_pos = 0;
    start_pos  = 0;
    target_len = (int) strlen(target);
    max_buffer_pos = -1;

    do {


        if (buffer_pos > max_buffer_pos) {
            buffer[buffer_pos] = (raw) ? getRawTexChar() : getTexChar();
            max_buffer_pos = buffer_pos;
        }

        if (buffer[buffer_pos] == '\0') {
            diagnostics(ERROR, "end of file reached before '%s' was found",target);
        }

        if (buffer[buffer_pos] == target[target_pos]) {
            if (target_pos == 0)
                start_pos = buffer_pos;
            target_pos++;
        }


        else if (target[target_pos] != '|') {

            if (target_pos > 0)
                buffer_pos = start_pos;
            target_pos = 0;


        } else if (buffer[buffer_pos] != ' ' && buffer[buffer_pos] != '\n') {


            target_pos++;
            if (buffer[buffer_pos] == target[target_pos]) {
                target_pos++;
            } else {
                buffer_pos = start_pos;
                target_pos = 0;
            }
        }

        if (0) {
        if (buffer[buffer_pos] != '\n')
            diagnostics(WARNING, "this char = <%c>, %d, %d, max=%d", buffer[buffer_pos], buffer_pos, target_pos, max_buffer_pos);
        else
            diagnostics(WARNING, "this char = <\\n>, %d, %d, max=%d", buffer[buffer_pos], buffer_pos, target_pos, max_buffer_pos);
        }

        buffer_pos++;


        if (buffer_pos == BUFFSIZE)
            diagnostics(ERROR, "Could not find <%s> in %d characters \n\
            Recompile with larger BUFFSIZE in getTexUntil() in parser.c", target, BUFFSIZE);

    } while (target_pos < target_len);


    buffer[start_pos] = '\0';

    PopTrackLineNumber();

    s = strdup(buffer);
    diagnostics(6, "getSpacedTexUntil result = %s", s);
    return s;
}
