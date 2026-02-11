lame_report_fnc(lame_report_function print_f, const char *format, ...)
{
    if (print_f) {
        va_list args;
        va_start(args, format);
        print_f(format, args);
        va_end(args);
    }
}
