DEH_TextStart(deh_context_t *context, char *line)
{
    char *from_text, *to_text;
    int fromlen, tolen;
    int i;

    if (sscanf(line, "Text %i %i", &fromlen, &tolen) != 2)
    {
        DEH_Warning(context, "Parse error on section start");
        return NULL;
    }


    if (!deh_allow_long_strings && tolen > TXT_MaxStringLength(fromlen))
    {
        DEH_Error(context, "Replacement string is longer than the maximum "
                           "possible in doom.exe");
        return NULL;
    }

    from_text = Z_Malloc(fromlen + 1, PU_STATIC, NULL);
    to_text = Z_Malloc(tolen + 1, PU_STATIC, NULL);


    for (i=0; i<fromlen; ++i)
    {
        int c;

        c = DEH_GetChar(context);

        from_text[i] = c;
    }

    from_text[fromlen] = '\0';


    for (i=0; i<tolen; ++i)
    {
        int c;

        c = DEH_GetChar(context);

        to_text[i] = c;
    }
    to_text[tolen] = '\0';

    DEH_AddStringReplacement(from_text, to_text);

    return NULL;
}
