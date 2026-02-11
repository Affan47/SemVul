kmo_strupper(char *s)
{
    char *t = NULL;

    KMO_TRY
    {
        KMO_TRY_ASSURE(s != NULL,
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data is provided!");
        t = s;

        while (*t) {
            *t = toupper(*t);
            t++;
        }
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();
        s = NULL;
    }

    return s;
}
