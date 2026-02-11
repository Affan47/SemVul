_pil_printerr(const char *format, ...)
{

    va_list args;
    char string[MAX_MESSAGE_LENGTH + 1];
    PilPrintFunc printer;


    if (format == NULL) {
        return;
    }

    va_start(args, format);

#ifdef HAVE_VSNPRINTF
    vsnprintf(string, (size_t) MAX_MESSAGE_LENGTH, format, args);
#else
    vsprintf(string, format, args);
#endif

    string[MAX_MESSAGE_LENGTH] = '\0';

    printer = pil_error_printer;

    if (printer != NULL) {
        printer(string);
    }
    else {
        fputs(string, stderr);
        fflush(stderr);
    }

    return;

}
