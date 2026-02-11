parse_chr(const char *field, size_t length, pio_status_t *status)
{
    char *endptr;
    unsigned char chr = (unsigned char) strtol( field, &endptr, 10 );
    if( length > 0 && ( endptr == NULL || *endptr == '\0' ) )
    {
        *status = PIO_OK;
        return chr;
    }

    *status = PIO_ERROR;
    return 0;
}
