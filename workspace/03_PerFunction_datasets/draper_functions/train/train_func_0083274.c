DBCSCharLength(int codePage, const char *s)
{

    if (codePage == 932 || codePage == 936 || codePage == 949 ||
        codePage == 950 || codePage == 1361) {
        return IsDBCSLeadByte(codePage, s[0]) ? 2 : 1;
    }
    return 1;

}
