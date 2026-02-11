app_str(const char * str) {
    while (*str && send_size < (int)sizeof(send_buf)) {
        send_buf[send_size++] = *str++;
    }
}
