printPointF2H(FILE * pf, const char *szImageDir, const char *szExtension,
              int iPoint0, int iPoint1, const int fColor, const int fUp, const htmlexportcss hecss)
{

    char sz[100];
    char szAlt[100];

    if (iPoint0) {


        sprintf(sz, "b-%c%c-o%d", fColor ? 'g' : 'y', fUp ? 'd' : 'u', (iPoint0 >= 11) ? 11 : iPoint0);
        sprintf(szAlt, "%1xX", iPoint0);

    } else if (iPoint1) {


        sprintf(sz, "b-%c%c-x%d", fColor ? 'g' : 'y', fUp ? 'd' : 'u', (iPoint1 >= 11) ? 11 : iPoint1);
        sprintf(szAlt, "%1xO", iPoint1);

    } else {

        sprintf(sz, "b-%c%c", fColor ? 'g' : 'y', fUp ? 'd' : 'u');
        sprintf(szAlt, "&nbsp;'");
    }

    printImage(pf, szImageDir, sz, szExtension, szAlt, hecss, HTML_EXPORT_TYPE_FIBS2HTML);

}
