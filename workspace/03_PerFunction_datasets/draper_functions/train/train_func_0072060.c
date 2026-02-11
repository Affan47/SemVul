ARTreadschema(void)
{
    const struct cvector        *standardoverview;
    const struct vector         *extraoverview;
    ARTOVERFIELD                *fp;
    unsigned int                i;


    standardoverview = overview_fields();
    extraoverview = overview_extra_fields(true);
    ARTfields = xmalloc((standardoverview->count + extraoverview->count + 1)
                        * sizeof(ARTOVERFIELD));


    for (i = 0, fp = ARTfields; i < standardoverview->count; i++) {
        fp->NeedsHeader = false;
        fp->HasHeader = false;
        fp->Header = xstrdup(standardoverview->strings[i]);
        fp->Length = strlen(standardoverview->strings[i]);
        fp++;
    }
    for (i = 0; i < extraoverview->count; i++) {
        fp->NeedsHeader = true;
        fp->HasHeader = false;
        fp->Header = xstrdup(extraoverview->strings[i]);
        fp->Length = strlen(extraoverview->strings[i]);
        fp++;
    }

    ARTfieldsize = fp - ARTfields;
}
