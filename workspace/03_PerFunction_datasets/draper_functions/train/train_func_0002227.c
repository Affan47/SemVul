DB_RemoveEnclosingSpaces (char *string)
{
    char *pc1, *pc2;


    for (pc2 = string; (*pc2 != '\0') && (*pc2 == ' '); pc2++);
    if (*pc2 == '\0') {
        string [0] = '\0';
        return;
    }


    if (pc2 != string) {
        for (pc1 = string; *pc2; pc1++, pc2++)
            *pc1 = *pc2;
        *pc1 = '\0';
    }


    for (pc2 = string + strlen (string) - 1; *pc2 == ' '; pc2--);
        pc2++;
    *pc2 = '\0';
}
