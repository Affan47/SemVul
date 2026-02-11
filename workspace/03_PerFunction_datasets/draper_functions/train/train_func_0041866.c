R_FlatNumForName(char *name)
{
    int i;
    char namet[9];

    i = W_CheckNumForName(name);
    if (i == -1)
    {
        namet[8] = 0;
        memcpy(namet, name, 8);
        I_Error("R_FlatNumForName: %s not found", namet);
    }
    return i - firstflat;
}
