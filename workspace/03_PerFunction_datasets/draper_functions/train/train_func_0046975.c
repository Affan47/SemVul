writeChars(unsigned char *frame, char const *str, size_t n)
{
    while (n--) {
        *frame++ = *str++;
    }
    return frame;
}
