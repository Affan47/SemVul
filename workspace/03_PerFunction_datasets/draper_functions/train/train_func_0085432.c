long2str(LONG num) {
    static char num2str_buffer[10];

    STRPTR result_str = NULL;

    if (sprintf(num2str_buffer, "%d", (int) num))
        result_str = num2str_buffer;
    return result_str;
}
