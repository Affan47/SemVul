ario_util_stristr (const char *haystack,
                   const char *needle)
{
        ARIO_LOG_FUNCTION_START;

        if (!needle || !*needle)
                return haystack;

        for (; *haystack; ++haystack) {
                if (toupper(*haystack) == toupper(*needle)) {


                        const char *h, *n;

                        for (h = haystack, n = needle; *h && *n; ++h, ++n) {
                                if (toupper(*h) != toupper(*n)) {
                                        break;
                                }
                        }

                        if (!*n) {

                                return haystack;
                        }
                }
        }
        return 0;
}
