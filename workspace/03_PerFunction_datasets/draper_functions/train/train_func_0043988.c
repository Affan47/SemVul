set_binary_form(const char *form)
{
    int bform = -1;

    if (HDstrcmp(form,"NATIVE") == 0 || HDstrcmp(form,"MEMORY") == 0) {

        bform = 0;
    }
    else if (HDstrcmp(form,"FILE") == 0)
        bform = 1;
    else if (HDstrcmp(form,"LE") == 0)
        bform = 2;
    else if (HDstrcmp(form,"BE") == 0)
        bform = 3;

    return bform;
}
