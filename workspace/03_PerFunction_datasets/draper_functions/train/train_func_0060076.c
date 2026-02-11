systemCodeset() const
{
    QByteArray codeset;
#if HAVE_LANGINFO_H


    codeset = nl_langinfo(CODESET);

    if ((codeset == "ANSI_X3.4-1968") || (codeset == "US-ASCII")) {

        codeset = "ISO-8859-1";
    }
#endif
    return codeset;
}
