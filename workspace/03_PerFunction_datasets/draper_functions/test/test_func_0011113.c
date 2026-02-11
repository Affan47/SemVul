SelectTypes(Types)


char *Types;
{
    struct ka BB;
    char TTmp[8];

    BB.kaLeft   = BB.kaRight = KicCursor.kcRawX;
    BB.kaBottom = BB.kaTop   = KicCursor.kcRawY;
    if (Types == NULL) {
        Selection(&BB);
        return;
    }
    strcpy(TTmp,Parameters.kpSelectTypes);
    strncpy(Parameters.kpSelectTypes,Types,8);
    Parameters.kpSelectTypes[7] = '\0';
    Selection(&BB);
    strcpy(Parameters.kpSelectTypes,TTmp);
}
