printw(int y, int x, const char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int result = ::wmove(w, y, x);
    if (result == OK) {
	result = ::vw_printw(w, fmt, args);
    }
    va_end(args);
    return result;
}
