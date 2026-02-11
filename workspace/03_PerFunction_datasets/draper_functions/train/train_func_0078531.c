strtof_gjay ( const char *nptr, char **endptr) {
    char * end;
    float base = 10.0;
    float divisor;
    float result = 0;

    result = strtol(nptr, &end, 10);
    if ((*end == '.') || (*end == ',')) {
        end++;
        divisor = base;
        while (isdigit(*end)) {
            result += (*end - '0') / divisor;
            divisor *= base;
            end++;
        }
    }
    if (endptr)
        *endptr = end;
    return result;
}
