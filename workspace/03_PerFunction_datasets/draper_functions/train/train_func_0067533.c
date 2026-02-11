rb_remark(const char *info, int perc, char *txt)
{
    char *txt2;

    txt2 = (char *) getmem(RMSTRLEN);
    sprintf(txt2, "%s%i%%", info, perc/100);
    if(txt) {
        strcat(txt, txt2);
        free(txt2);
    }
    else {
        txt = txt2;
    }

    return txt;
}
