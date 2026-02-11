lwarning(const Lexeme &t, const char *format, ...)
{
    va_list val;
    va_start(val, format);
    xlerror(t.pos1(), t.pos2(), _file.landmark(), ErrorHandler::e_warning, format, val);
    va_end(val);
    return -1;
}
