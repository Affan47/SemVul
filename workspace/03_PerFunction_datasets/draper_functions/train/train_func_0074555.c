textrecordfield (const char * dbname)
{
    if (!strcmp (dbname, "main"))
    {
        return 1;
    }
    else if (!strcmp (dbname, "daily"))
    {
        return 2;
    }
    else if (!strcmp (dbname, "bytecode"))
    {
        return 7;
    }
    else if (!strcmp (dbname, "safebrowsing"))
    {
        return 6;
    }
    return 0;
}
