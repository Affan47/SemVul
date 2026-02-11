receive_erlang_port_msg(void)
{
    int i, len = 0;
    byte *buffer;
    byte lengthstr[LENGTH_INDICATOR_SIZE];

    if(read_exact(lengthstr, LENGTH_INDICATOR_SIZE) !=
       LENGTH_INDICATOR_SIZE)
    {
	DO_EXIT(EXIT_STDIN_HEADER);
    }
    for(i=0; i < LENGTH_INDICATOR_SIZE; i++) {
	len <<= 8;
	len |= lengthstr[i];
    }

    if (len <= 0 || len > 1024) {
	DO_EXIT(EXIT_STDIN_HEADER);
    }

    buffer = (byte *)safe_malloc(len);

    if (read_exact(buffer, len) <= 0) {
	DO_EXIT(EXIT_STDIN_BODY);
    }

    if (buffer[len-1] != '\0') {
	DO_EXIT(EXIT_STDIN_BODY);
    }

    return buffer;
}
