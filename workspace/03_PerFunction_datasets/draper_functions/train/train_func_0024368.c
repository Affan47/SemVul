ChooseEncoding (Xi18n i18n_core,
                             IMEncodingNegotiationStruct *enc_nego)
{
    Xi18nAddressRec *address = (Xi18nAddressRec *) & i18n_core->address;
    XIMEncodings *p;
    int i, j;
    int enc_index=0;

    p = (XIMEncodings *) &address->encoding_list;
    for (i = 0;  i < (int) p->count_encodings;  i++)
    {
        for (j = 0;  j < (int) enc_nego->encoding_number;  j++)
        {
            if (strcmp (p->supported_encodings[i],
                        enc_nego->encoding[j].name) == 0)
            {
                enc_index = j;
                break;
            }

        }

    }


    return (INT16) enc_index;
#if 0
    return (INT16) XIM_Default_Encoding_IDX;
#endif
}
