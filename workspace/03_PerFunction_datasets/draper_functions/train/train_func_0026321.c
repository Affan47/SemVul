printf(const char* fmt, ...) {
    va_list arg_list;
    va_start(arg_list, fmt);
    print(vformat(fmt, arg_list));
    va_end(arg_list);
}
