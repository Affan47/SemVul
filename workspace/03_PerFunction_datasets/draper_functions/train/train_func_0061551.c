errorcntl()
{
    char estr[256], *ep = estr;

    while( ch != EOL ) {
       if (ep < estr+sizeof(estr)-2 )
	  *ep++ = ch;
       gch1();
    }
    *ep = 0;

    if (!orig_cppmode)
       error(estr);
    else {
       outstr("#error");
       outnstr(estr);
    }
}
