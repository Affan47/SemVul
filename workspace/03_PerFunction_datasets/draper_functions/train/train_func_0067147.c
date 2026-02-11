getnum(char *string)
{
    unsigned char c;
    aa_puts(context, 0, 0, AA_SPECIAL, string);
    aa_flush(context);
    while (((c = tolower(aa_getkey(context, 1))) < '0' || c > '9') && (c<'A' || c>'Z') && (c<'a' || c>'z'));
    if(c=='0') return 9;
    if(c<='9'&&c>='1') return (c-'1');
    if(c>='a'&&c<='z') return (c-'a'+10);
    if(c>='A'&&c<='Z') return (c-'A'+10);
    return (c - '0');
}
