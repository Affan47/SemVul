seqDesSwiss(const AjPStr str)
{
    SeqEDesSwiss ides = SWISS_DES_UNK;
    const char* cp = MAJSTRGETPTR(str);

    switch (*cp)
    {
        case 'A':
            if(!strcmp(cp, "AltName:")) ides = SWISS_DES_ALT;
            break;
        case 'C':
            if(!strcmp(cp, "Contains:")) ides = SWISS_DES_CONT;
            break;
        case 'F':
            if(!strcmp(cp, "Flags:")) ides = SWISS_DES_FLG;
            break;
        case 'I':
            if(!strcmp(cp, "Includes:")) ides = SWISS_DES_INC;
            break;
        case 'R':
            if(!strcmp(cp, "RecName:")) ides = SWISS_DES_REC;
            break;
        case 'S':
            if(!strcmp(cp, "SubName:")) ides = SWISS_DES_SUB;
            break;
        default:
            ides = SWISS_DES_UNK;
            break;
    }

    return ides;
}
