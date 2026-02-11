skip_spaces()
{
    int c = buffer_peek_char();

    while ((c != -1) && isspace(c)) {
        buffer_next_char();
        c = buffer_peek_char();
    }
}
