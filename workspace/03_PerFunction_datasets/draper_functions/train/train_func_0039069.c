Get_Browser_Type(char *prot)
{
    BrType bt = bt_unknown;
    if (InStr(prot,(char *)"MSIE"))
        bt = bt_msie;
    else if (InStr(prot,(char *)"Chrome"))
        bt = bt_opera;
    else if (InStr(prot,(char *)"Opera"))
        bt = bt_opera;
    else if (InStr(prot,(char *)"Safari"))
        bt = bt_safari;
    else if (InStr(prot,(char *)"Navigator"))
        bt = bt_ns;
    else if (InStr(prot,(char *)"Firefox"))
        bt = bt_firefox;
    else if (InStr(prot,(char *)"Lynx"))
        bt = bt_lynx;
    else if (InStr(prot,(char *)"Wget"))
        bt = bt_wget;
    else if (InStr(prot,(char *)"Mozilla"))
        bt = bt_moz;

    return bt;
}
