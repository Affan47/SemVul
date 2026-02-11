qfits_is_boolean(const char * s)
{
    if (s==NULL) return 0;
    if (s[0]==0) return 0;
    if ((int)strlen(s)>1) return 0;
    if (s[0]=='T' || s[0]=='F') return 1;
    return 0;
}
