Csprintf(Cstring *iot, char *fmt, ...)
{
    va_list ptr;
    int siz=100;

    do {
	RESERVE(*iot, siz);
	va_start(ptr, fmt);
	siz = vsnprintf(T(*iot)+S(*iot), ALLOCATED(*iot)-S(*iot), fmt, ptr);
	va_end(ptr);
    } while ( siz > (ALLOCATED(*iot)-S(*iot)) );

    S(*iot) += siz;
    return siz;
}
