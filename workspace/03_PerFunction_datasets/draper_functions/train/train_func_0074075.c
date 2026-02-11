currentdb (const char *dbname, char *localname)
{
    char db[32];
    struct cl_cvd *cvd = NULL;


    snprintf (db, sizeof (db), "%s.cvd", dbname);
    if (localname)
        strcpy (localname, db);

    if (access (db, R_OK) == -1)
    {
        snprintf (db, sizeof (db), "%s.cld", dbname);
        if (localname)
            strcpy (localname, db);
    }

    if (!access (db, R_OK))
        cvd = cl_cvdhead (db);

    return cvd;
}
