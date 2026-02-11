parse_positive_number_arg(char *s, char *name)
{
    char *end_ptr;
    unsigned long result;
    errno = 0;
    result = strtoul(s, &end_ptr, 10);
    if (errno) {
        die(name, strerror(errno));
    }
    if (*s == '\0') {
        die(name, "argument value cannot be empty");
    }
    if (*end_ptr != '\0') {
        die(name, "invalid value");
    }
    if (! result) {
        die(name, "must be a positive number");
    }
    return result;
}
