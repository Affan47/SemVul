GetEncodings(Xi18n i18n_core, XIMEncodings **p_encoding)
{
    Xi18nAddressRec *address = (Xi18nAddressRec *) &i18n_core->address;
    XIMEncodings *p;
    int	i;

    p = &address->encoding_list;

    if ((*p_encoding = (XIMEncodings *) malloc (sizeof (XIMEncodings)
                                              + p->count_encodings*sizeof(XIMEncoding))) == NULL)
    {
        return False;
    }

    (*p_encoding)->count_encodings = p->count_encodings;
    (*p_encoding)->supported_encodings =
        (XIMEncoding *) ((XPointer)*p_encoding + sizeof (XIMEncodings));
    for (i = 0;  i < (int) p->count_encodings;  i++)
    {
        (*p_encoding)->supported_encodings[i]
            = (char *) malloc (strlen (p->supported_encodings[i]) + 1);
        strcpy ((*p_encoding)->supported_encodings[i],
                p->supported_encodings[i]);
    }

    return True;
}
