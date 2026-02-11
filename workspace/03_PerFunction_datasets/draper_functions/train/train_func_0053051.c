ffgknm( char *card,
            char *name,
            int *length,
            int  *status)


{
    char *ptr1, *ptr2;
    int ii;

    *name = '\0';
    *length = 0;


    if (FSTRNCMP(card, "HIERARCH ", 9) == 0)
    {
        ptr2 = strchr(card, '=');

        if (!ptr2)
        {

            strcat(name, "HIERARCH");
            *length = 8;
            return(*status);
        }


        ptr1 = &card[9];
        while (*ptr1 == ' ')
            ptr1++;

        strncat(name, ptr1, ptr2 - ptr1);
        ii = ptr2 - ptr1;

        while (ii > 0 && name[ii - 1] == ' ')
            ii--;

        name[ii] = '\0';
        *length = ii;
    }
    else
    {
        for (ii = 0; ii < 8; ii++)
        {

           if (*(card+ii) != ' ' && *(card+ii) !='\0')
           {
               *(name+ii) = *(card+ii);
           }
           else
           {
               name[ii] = '\0';
               *length = ii;
               return(*status);
           }
        }


        name[8] = '\0';
        *length = 8;
    }

    return(*status);
}
