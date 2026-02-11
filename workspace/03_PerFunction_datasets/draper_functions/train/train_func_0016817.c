cfapi_cost_string_from_value(int *type, ...) {
    StringBuffer *sb;
    uint64 cost;
    char *buffer, *final;
    int length, largest_coin;
    va_list args;

    va_start(args, type);
    cost = va_arg(args, uint64);
    largest_coin = va_arg(args, int);
    buffer = va_arg(args, char*);
    length = va_arg(args, int);
    va_end(args);

    *type = CFAPI_NONE;

    if (length < 1)
        return;

    sb = cost_string_from_value(cost, largest_coin, NULL);
    final = stringbuffer_finish(sb);

    strncpy(buffer, final, length - 1);
    buffer[length - 1] = '\0';
    free(final);
}
