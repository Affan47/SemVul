tk_cmp(Token *tk1, Token *tk2)
{
    int cmp;
    if (tk1->start > tk2->start) {
        cmp = 1;
    }
    else if (tk1->start < tk2->start) {
        cmp = -1;
    }
    else {
        if (tk1->end > tk2->end) {
            cmp = 1;
        }
        else if (tk1->end < tk2->end) {
            cmp = -1;
        }
        else {
            cmp = strcmp((char *)tk1->text, (char *)tk2->text);
        }
    }
    return cmp;
}
