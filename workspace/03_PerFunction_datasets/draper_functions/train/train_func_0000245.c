uprv_getPOSIXID(void)
{
    static const char* posixID = NULL;
    if (posixID == 0) {


        posixID = setlocale(LC_CTYPE, NULL);
        if ((posixID == 0)
            || (uprv_strcmp("C", posixID) == 0)
            || (uprv_strcmp("POSIX", posixID) == 0))
        {

            posixID = getenv("LC_ALL");
            if (posixID == 0) {
                posixID = getenv("LC_CTYPE");
                if (posixID == 0) {
                    posixID = getenv("LANG");
                }
            }
        }

        if ((posixID==0)
            || (uprv_strcmp("C", posixID) == 0)
            || (uprv_strcmp("POSIX", posixID) == 0))
        {

            posixID = "en_US_POSIX";
        }
    }

    return posixID;
}
